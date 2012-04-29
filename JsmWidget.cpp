/****************************************************************************
 ** Deling Final Fantasy VIII Field Editor
 ** Copyright (C) 2009-2012 Arzel J�r�me <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "JsmWidget.h"

JsmWidget::JsmWidget(QWidget *parent)
	: PageWidget(parent), jsmFile(NULL), groupID(-1), methodID(-1)
{
//	build();
}

void JsmWidget::build()
{
	if(isBuilded())	return;

	QFont font;
	font.setPointSize(8);

	list1 = new QTreeWidget(this);
	list1->setHeaderLabels(QStringList() << tr("Id") << tr("Groupe"));
	list1->setFixedWidth(180);
	list1->setAutoScroll(false);
	list1->setIndentation(0);
	list1->setFont(font);
	list1->setUniformRowHeights(true);

	list2 = new QTreeWidget(this);
	list2->setHeaderLabels(QStringList() << tr("Id") << tr("Script") << tr("Script label") << tr("Sp�cial"));
	list2->setFixedWidth(180);
	list2->setAutoScroll(false);
	list2->setIndentation(0);
	list2->setFont(font);
	list2->setUniformRowHeights(true);

	PlainTextEdit *te = new PlainTextEdit(this);
	textEdit = te->textEdit();
	QFont font2 = textEdit->document()->defaultFont();
	font2.setStyleHint(QFont::TypeWriter);
	font2.setFamily("Courrier");
	textEdit->document()->setDefaultFont(font2);
	new JsmHighlighter(textEdit->document());
	// continue highlight when window is inactive
	QPalette pal = textEdit->palette();
	pal.setColor(QPalette::Inactive, QPalette::Highlight, pal.color(QPalette::Active, QPalette::Highlight));
	pal.setColor(QPalette::Inactive, QPalette::HighlightedText, pal.color(QPalette::Active, QPalette::HighlightedText));
	textEdit->setPalette(pal);

	errorLabel = new QLabel(this);
	QWidget *errorWidget = new QWidget(this);

	QHBoxLayout *errorLayout = new QHBoxLayout(errorWidget);
	errorLayout->addStretch();
	errorLayout->addWidget(errorLabel);

	toolBar = new QToolBar(this);
	QAction *compileAction = toolBar->addAction(tr("Compiler"), this, SLOT(compile()));
	compileAction->setToolTip(tr("Compiler (Ctrl+B)"));
	compileAction->setStatusTip(tr("Compiler (Ctrl+B)"));
	compileAction->setShortcutContext(Qt::ApplicationShortcut);
	compileAction->setShortcut(QKeySequence("Ctrl+B"));
	toolBar->addWidget(errorWidget);
	toolBar->setEnabled(false);

	QGridLayout *mainLayout = new QGridLayout(this);
	mainLayout->addWidget(list1, 0, 0, 2, 1);
	mainLayout->addWidget(list2, 0, 1, 2, 1);
	mainLayout->addWidget(te, 0, 2);
	mainLayout->addWidget(textEdit, 0, 3);
	mainLayout->addWidget(toolBar, 1, 2, 1, 2);
	mainLayout->setContentsMargins(QMargins());

	connect(list1, SIGNAL(itemSelectionChanged()), SLOT(fillList2()));
	connect(list2, SIGNAL(itemSelectionChanged()), SLOT(fillTextEdit()));

	PageWidget::build();
}

void JsmWidget::compile()
{
	groupID = currentItem(list1);
	methodID = currentItem(list2);
	if(groupID==-1 || methodID==-1)	return;

	QString errorStr;
	QPalette pal = errorLabel->palette();
	int l = jsmFile->fromString(groupID, methodID, textEdit->toPlainText(), errorStr);
	if(l != 0) {
		pal.setColor(QPalette::Active, QPalette::ButtonText, Qt::darkRed);
		pal.setColor(QPalette::Inactive, QPalette::ButtonText, Qt::darkRed);
		errorLabel->setPalette(pal);
		errorLabel->setText(l != -1 ? tr("Ligne %1 -> %2").arg(l).arg(errorStr) : errorStr);
	} else {
		pal.setColor(QPalette::Active, QPalette::ButtonText, Qt::darkGreen);
		pal.setColor(QPalette::Inactive, QPalette::ButtonText, Qt::darkGreen);
		errorLabel->setPalette(pal);
		errorLabel->setText(tr("Compil� avec succ�s"));
		emit modified(true);
	}
}

void JsmWidget::clear()
{
	if(!isBuilded())	return;

	list1->blockSignals(true);
	list2->blockSignals(true);

	if(jsmFile != NULL)	saveSession();

	list1->clear();
	list2->clear();
	textEdit->clear();
	errorLabel->clear();

	list1->blockSignals(false);
	list2->blockSignals(false);

	PageWidget::clear();
}

void JsmWidget::saveSession()
{
	jsmFile->setCurrentOpcodeScroll(this->groupID, this->methodID, textEdit->verticalScrollBar()->value(), textEdit->textCursor());
	if(textEdit->document()->isModified())
		jsmFile->setDecompiledScript(this->groupID, this->methodID, textEdit->toPlainText());
}

void JsmWidget::setReadOnly(bool readOnly)
{
	if(isBuilded()) {
		textEdit->setReadOnly(readOnly);
		toolBar->setEnabled(!readOnly);
	}

	PageWidget::setReadOnly(readOnly);
}

void JsmWidget::fillList1(JsmFile *jsmFile)
{
	PageWidget::fill();

//	qDebug() << "JsmWidget::fillList1(jsmFile)";
//	qDebug() << jsmFile->printCount();

	if(this->jsmFile != NULL) {
		saveSession();
		this->methodID = this->groupID = -1;
	}

	this->jsmFile = jsmFile;
	int groupID = jsmFile->currentGroupItem();

	list1->clear();
	list1->addTopLevelItems(nameList());
	list1->scrollToTop();
	list1->resizeColumnToContents(0);
	list1->resizeColumnToContents(1);
	list1->resizeColumnToContents(2);

	QTreeWidgetItem *item = list1->topLevelItem(groupID);
	if(item) 	list1->setCurrentItem(item);
}

void JsmWidget::fillList2()
{
//	qDebug() << QString("JsmWidget::fillList2(%1)").arg(currentItem(list1));

	list2->clear();
	int groupID = currentItem(list1);
	if(groupID==-1)	return;
	int methodID = jsmFile->currentMethodItem(groupID);

	list2->addTopLevelItems(methodList(groupID));
	list2->scrollToTop();
	list2->resizeColumnToContents(0);
	list2->resizeColumnToContents(1);
	list2->resizeColumnToContents(2);

	QTreeWidgetItem *item = list2->topLevelItem(methodID);
	if(item) 	list2->setCurrentItem(item);
}

void JsmWidget::fillTextEdit()
{
//	qDebug() << QString("JsmWidget::fillTextEdit(%1, %2)").arg(currentItem(list1)).arg(currentItem(list2));

	saveSession();
	textEdit->clear();
	groupID = currentItem(list1);
	methodID = currentItem(list2);
	if(groupID==-1 || methodID==-1) {
		toolBar->setEnabled(false);
		return;
	}

	int scroll = jsmFile->currentOpcodeScroll(groupID, methodID);
	int anchor;
	int position = jsmFile->currentTextCursor(groupID, methodID, anchor);

	textEdit->setPlainText(jsmFile->toString(groupID, methodID));
	if(!isReadOnly())	toolBar->setEnabled(true);

	if(position >= 0) {
		QTextCursor newCursor = textEdit->textCursor();
		newCursor.setPosition(anchor);
		newCursor.setPosition(position, QTextCursor::KeepAnchor);
		textEdit->setTextCursor(newCursor);
	}
	textEdit->verticalScrollBar()->setValue(scroll);
}

QList<QTreeWidgetItem *> JsmWidget::nameList() const
{
	QList<QTreeWidgetItem *> items;
	QTreeWidgetItem *item;
	int nbGroup = jsmFile->getScripts().nbGroup();
	int directorCount=0, squallCount=0, zellCount=0, irvineCount=0, quistisCount=0;
	int rinoaCount=0, selphieCount=0, seiferCount=0, edeaCount=0, lagunaCount=0, kirosCount=0;
	int wardCount=0, drawPointCount=0, eventLineCount=0, doorCount=0;

	for(int groupID=0 ; groupID<nbGroup ; ++groupID) {
		const JsmGroup &grp = jsmFile->getScripts().group(groupID);
		QString name = grp.name();
		item = new QTreeWidgetItem(QStringList() << QString("%1").arg(groupID, 3) << QString());
		item->setData(0, Qt::UserRole, groupID);
		switch(grp.type()) {
		case JsmGroup::Main:
			if(name.isEmpty())	name = QString("Director%1").arg(directorCount);
			directorCount++;
			item->setIcon(0, QIcon(":/images/main.png"));
			break;
		case JsmGroup::Model:
			switch(grp.character()) {
			case 0:
				if(name.isEmpty())	name = QString("Squall%1").arg(squallCount);
				squallCount++;
				item->setIcon(0, QIcon(":/images/icon-squall.png"));
				break;
			case 1:
				if(name.isEmpty())	name = QString("Zell%1").arg(zellCount);
				zellCount++;
				item->setIcon(0, QIcon(":/images/icon-zell.png"));
				break;
			case 2:
				if(name.isEmpty())	name = QString("Irvine%1").arg(irvineCount);
				irvineCount++;
				item->setIcon(0, QIcon(":/images/icon-irvine.png"));
				break;
			case 3:
				if(name.isEmpty())	name = QString("Quistis%1").arg(quistisCount);
				quistisCount++;
				item->setIcon(0, QIcon(":/images/icon-quistis.png"));
				break;
			case 4:
				if(name.isEmpty())	name = QString("Rinoa%1").arg(rinoaCount);
				rinoaCount++;
				item->setIcon(0, QIcon(":/images/icon-rinoa.png"));
				break;
			case 5:
				if(name.isEmpty())	name = QString("Selphie%1").arg(selphieCount);
				selphieCount++;
				item->setIcon(0, QIcon(":/images/icon-selphie.png"));
				break;
			case 6:
				if(name.isEmpty())	name = QString("Seifer%1").arg(seiferCount);
				seiferCount++;
				item->setIcon(0, QIcon(":/images/icon-seifer.png"));
				break;
			case 7:
				if(name.isEmpty())	name = QString("Edea%1").arg(edeaCount);
				edeaCount++;
				item->setIcon(0, QIcon(":/images/icon-edea.png"));
				break;
			case 8:
				if(name.isEmpty())	name = QString("Laguna%1").arg(lagunaCount);
				lagunaCount++;
				item->setIcon(0, QIcon(":/images/icon-laguna.png"));
				break;
			case 9:
				if(name.isEmpty())	name = QString("Kiros%1").arg(kirosCount);
				kirosCount++;
				item->setIcon(0, QIcon(":/images/icon-kiros.png"));
				break;
			case 10:
				if(name.isEmpty())	name = QString("Ward%1").arg(wardCount);
				wardCount++;
				item->setIcon(0, QIcon(":/images/icon-ward.png"));
				break;
			case -1:
				item->setIcon(0, QIcon(":/images/3d_model.png"));
				break;
			case DRAWPOINT_CHARACTER:
				if(name.isEmpty())	name = QString("DrawPoint%1").arg(drawPointCount);
				drawPointCount++;
				item->setIcon(0, QIcon(":/images/icon-drawpoint.png"));
				break;
			default:
				item->setIcon(0, QIcon(":/images/icon-unknown.png"));
				break;
			}
			break;
		case JsmGroup::Location:
			if(name.isEmpty())	name = QString("EventLine%1").arg(eventLineCount);
			eventLineCount++;
			item->setIcon(0, QIcon(":/images/location.png"));
			break;
		case JsmGroup::Door:
			if(name.isEmpty())	name = QString("Door%1").arg(doorCount);
			doorCount++;
			item->setIcon(0, QIcon(":/images/door.png"));
			break;
		case JsmGroup::Background:
			item->setIcon(0, QIcon(":/images/background.png"));
			break;
		default:
			QPixmap pixnull(32, 32);
			pixnull.fill(Qt::transparent);
			item->setIcon(0, QIcon(pixnull));
			break;
		}
		if(name.isEmpty()) 	name = QString("Module%1").arg(groupID);
		item->setText(1, name);
		items.append(item);
	}

	return items;
}

QList<QTreeWidgetItem *> JsmWidget::methodList(int groupID) const
{
	QList<QTreeWidgetItem *> items;
	QTreeWidgetItem *item;
	int begin, count;
	QString name;

	if(jsmFile->getScripts().nbGroup()<=groupID) {
		qWarning() << "JsmFile::methodList error 1" << groupID << jsmFile->getScripts().nbGroup();
		return items;
	}

	JsmGroup::Type groupType = jsmFile->getScripts().group(groupID).type();

	begin = jsmFile->getScripts().firstMethodID(groupID);
	count = jsmFile->getScripts().nbScript(groupID);

	if(jsmFile->getScripts().nbScript()<begin+count) {
		qWarning() << "JsmFile::methodList error 2" << jsmFile->getScripts().nbScript() << (begin+count);
		return items;
	}

	for(int methodID=0 ; methodID<count ; ++methodID)
	{
		const JsmScript &script = jsmFile->getScripts().script(groupID, methodID);
		if(methodID==0) {
			name = QString();
		}
		else {
			name = script.name();
			if(name.isEmpty()) {
				if(methodID==1) {
					name = "default";
				} else {
					switch(groupType) {
					case JsmGroup::Model:
						switch(methodID) {
						case 2:		name = "talk";		break;
						case 3:		name = "push";		break;
						}
						break;
					case JsmGroup::Location:
						switch(methodID) {
						case 2:		name = "talk";		break;
						case 3:		name = "push";		break;
						case 4:		name = "across";	break;
						case 5:		name = "touch";		break;
						case 6:		name = "touchoff";	break;
						case 7:		name = "touchon";	break;
						}
						break;
					case JsmGroup::Door:
						switch(methodID) {
						case 2:		name = "open";		break;
						case 3:		name = "close";		break;
						case 4:		name = "on";		break;
						case 5:		name = "off";		break;
						}
						break;
					default:
						break;
					}
					if(name.isEmpty())		name = QString("Method%1").arg(methodID);
				}
			}
		}
		item = new QTreeWidgetItem(QStringList() << QString("%1").arg(methodID, 3) << name << QString("%1").arg(begin+methodID, 3) << QString("%1").arg(script.flag() ? QObject::tr("Oui") : QString()));
		item->setData(0, Qt::UserRole, methodID);
		items.append(item);
	}

	return items;
}

int JsmWidget::currentItem(QTreeWidget *list)
{
	QList<QTreeWidgetItem *> items = list->selectedItems();
	if(items.isEmpty())	return -1;

	return items.first()->data(0, Qt::UserRole).toInt();
}

//void JsmWidget::jump(QTreeWidgetItem *item)
//{
//	QList<QTreeWidgetItem *> items;

//	if(item==NULL)	return;
//	bool ok;
//	uint pos, raw, key;

//	raw = item->text(2).toUInt(&ok, 16);
//	if(!ok) return;
//	key = raw>>24;

//	if(key == 2 || key == 3) {
//		pos = item->text(3).toUInt(&ok);
//		if(!ok) return;

//		if(key == 2)
//			pos += (qint16)(raw & 0x0000FFFF);
//		else
//			pos += raw & 0x0000FFFF;

//		items = list3->findItems(QString().setNum(pos), Qt::MatchExactly, 3);
//		if(items.isEmpty())	return;

//		item = list3->itemAbove(items.first());
//		list3->setCurrentItem(item);
//		list3->scrollToItem(item);
//	}
//	else if((key == 20 || key == 21 || key == 22) && list3->topLevelItemCount() > 2) {
//		int group = item->text(1).toUInt(&ok);
//		if(!ok) return;

//		int label = list3->itemAbove(item)->text(1).toUInt(&ok);
//		if(!ok) return;

//		gotoScriptLabel(group, label);
//	}
//}

void JsmWidget::gotoScript(int groupID, int methodID, int opcodeID)
{
	if(!isBuilded())	build();

	QList<QTreeWidgetItem *> items = list1->findItems(QString("%1").arg(groupID, 3), Qt::MatchExactly);
	QTreeWidgetItem *item;
	if(items.isEmpty())	return;

	item = items.first();
	list1->setCurrentItem(item);
	list1->scrollToItem(item);

	items = list2->findItems(QString("%1").arg(methodID, 3), Qt::MatchExactly);
	if(items.isEmpty())	return;

	item = items.first();
	list2->setCurrentItem(item);
	list2->scrollToItem(item);

	QTextCursor cursor = textEdit->textCursor();
	cursor.setPosition(textEdit->document()->findBlockByLineNumber(jsmFile->opcodePositionInText(groupID, methodID, opcodeID)).position());
	cursor.movePosition(QTextCursor::StartOfLine);
	cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
	textEdit->setTextCursor(cursor);
	textEdit->ensureCursorVisible();
}

//void JsmWidget::gotoScriptLabel(int groupID, int labelID)
//{
//	QList<QTreeWidgetItem *> items = list1->findItems(QString("%1").arg(groupID, 3), Qt::MatchExactly);
//	QTreeWidgetItem *item;
//	if(items.isEmpty())	return;

//	item = items.first();
//	list1->setCurrentItem(item);
//	list1->scrollToItem(item);

//	items = list2->findItems(QString("%1").arg(labelID, 3), Qt::MatchExactly, 2);
//	if(items.isEmpty())	return;

//	item = items.first();
//	list2->setCurrentItem(item);
//	list2->scrollToItem(item);

//	if(list3->topLevelItemCount()<1)	return;
//	list3->scrollToItem(list3->topLevelItem(0));
//}

int JsmWidget::selectedOpcode()
{
	if(!isBuilded())	return 0;

	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition(QTextCursor::StartOfWord);
	cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
	int index;
	if((index = JsmFile::opcodeName.indexOf(cursor.selectedText().toUpper())) != -1) {
		return index;
	}
	return 0;
}
