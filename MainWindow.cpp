/****************************************************************************
 ** Deling Final Fantasy VIII Field Editor
 ** Copyright (C) 2009-2012 Arzel Jérôme <myst6re@gmail.com>
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
#include "MainWindow.h"
#include "parameters.h"
#include "Config.h"
#include "Data.h"
#include "ProgressWidget.h"
#include "ScriptExporter.h"
#include "EncounterExporter.h"
#include "BackgroundExporter.h"
#include "widgets/MsdWidget.h"
#include "widgets/JsmWidget.h"
#include "widgets/CharaWidget.h"
#include "widgets/WalkmeshWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/EncounterWidget.h"
#include "widgets/TdwWidget.h"
#include "widgets/SoundWidget.h"
#include "widgets/MiscWidget.h"
#include "widgets/AboutDialog.h"
#include "QElapsedTimer"
#include <QScreen>

MainWindow::MainWindow()
    : fieldArchive(nullptr), field(nullptr), currentField(nullptr),
      fieldThread(new FieldThread), file(nullptr), menuGameLang(nullptr),
      fsDialog(nullptr), _varManager(nullptr), firstShow(true)
{
    setMinimumSize(700, 600);
    resize(Config::value("mainWindowSize", QSize(768, 502)).toSize());
    if (Config::value("mainWindowMaximized", true).toBool())
        setWindowState(Qt::WindowMaximized);

    statusBar()->show();
    currentPath = new QLabel();
    statusBar()->addPermanentWidget(currentPath);

    QMenuBar *menuBar = new QMenuBar(this);

    /* Menu 'Fichier' */
    QMenu *menu = menuBar->addMenu(tr("&Fichier"));

    QAction *actionOpen = menu->addAction(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton), tr("&Ouvrir..."), QKeySequence::Open);
    actionGameLang = menu->addAction(tr("Changer la langue du jeu"));
    actionGameLang->setVisible(false);
    actionSave = menu->addAction(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton), tr("Enregi&strer"), QKeySequence::Save, this, &MainWindow::save);
    actionSaveAs = menu->addAction(tr("Enre&gistrer Sous..."), QKeySequence::SaveAs);
    actionExport = menu->addAction(tr("Exporter..."), this, &MainWindow::exportCurrent);
    menuExportAll = menu->addMenu(tr("Exporter tout"));
    menuExportAll->addAction(tr("Scripts..."), this, &MainWindow::exportAllScripts);
    menuExportAll->addAction(tr("Rencontres aléatoires..."), this, &MainWindow::exportAllEncounters);
    menuExportAll->addAction(tr("Décors..."), this, &MainWindow::exportAllBackground);
    actionImport = menu->addAction(tr("Importer..."), this, &MainWindow::importCurrent);
    actionOpti = menu->addAction(tr("Optimiser l'archive..."), this, &MainWindow::optimizeArchive);
    menu->addSeparator();
    menu->addAction(tr("Plein écran"), Qt::Key_F11, this, &MainWindow::fullScreen);
    actionClose = menu->addAction(QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton), tr("Fe&rmer"), this, &MainWindow::closeFiles);
    menu->addAction(tr("&Quitter"), this, &MainWindow::close)->setMenuRole(QAction::QuitRole);

    menu = menuBar->addMenu(tr("&Outils"));
    actionFind = menu->addAction(QIcon(":/images/find.png"), tr("Rec&hercher..."), QKeySequence::Find, this, &MainWindow::search);
    menu->addAction(tr("&Var manager..."), this, &MainWindow::varManager);
    //menu->addAction(tr("&Rechercher tout..."), this, &MainWindow::miscSearch);
    actionRun = menu->addAction(QIcon(":/images/ff8.png"), tr("&Lancer FF8..."), Qt::Key_F8, this, &MainWindow::runFF8);
    actionRun->setShortcutContext(Qt::ApplicationShortcut);
    actionRun->setEnabled(Data::ff8Found());
    addAction(actionRun);

#ifndef Q_OS_MAC
    menuBar->addAction(tr("Op&tions"), this, &MainWindow::configDialog)->setMenuRole(QAction::PreferencesRole);
    menuBar->addAction(tr("&?"), this, &MainWindow::about)->setMenuRole(QAction::AboutRole);
#else
    menu->addAction(tr("Op&tions"), this, &MainWindow::configDialog)->setMenuRole(QAction::PreferencesRole);
    menu->addAction(tr("&?"), this, &MainWindow::about)->setMenuRole(QAction::AboutRole);
#endif

    setMenuBar(menuBar);

    toolBar = new QToolBar(tr("Barre d'outils &principale"));
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
    toolBar->addSeparator();
    toolBar->addAction(actionFind);
    toolBar->addAction(actionRun);
    toolBar->addAction(actionGameLang);

    list1 = new QTreeWidget();
    list1->setHeaderLabels(QStringList() << tr("Fichier") << tr("Description") << tr("#"));
    list1->setIndentation(0);
    list1->setSortingEnabled(true);
    list1->setAutoScroll(false);
    list1->setColumnWidth(2, 28);
    list1->sortByColumn(Config::value("list1ColumnSort", 2).toInt(), Qt::AscendingOrder);
    list1->setUniformRowHeights(true);
    list1->header()->setStretchLastSection(false);
    list1->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    list1->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    lineSearch = new QLineEdit();
    lineSearch->setFixedWidth(320);
    lineSearch->setStatusTip(tr("Recherche rapide"));

    bgPreview = new BGPreview();
    bgPreview->setFixedHeight(224);
    bgPreview->setFixedWidth(320);

    pageWidgets.append(new MsdWidget());
    pageWidgets.append(new JsmWidget());
    pageWidgets.append(new CharaWidget());
    pageWidgets.append(new WalkmeshWidget());
    pageWidgets.append(new BackgroundWidget());
    pageWidgets.append(new EncounterWidget());
    pageWidgets.append(new TdwWidget());
    pageWidgets.append(new SoundWidget());
    pageWidgets.append(new MiscWidget());

    tabBar = new QTabBar();
    for (PageWidget *pageWidget : pageWidgets)
        tabBar->addTab(pageWidget->tabName());
    tabBar->addTab(tr("Import/Export"));
    tabBar->setDrawBase(false);
    QWidget *tabBarWidget = new QWidget();
    QHBoxLayout *tabBarLayout = new QHBoxLayout(tabBarWidget);
    tabBarLayout->addStretch();
    tabBarLayout->addWidget(tabBar);
    tabBarLayout->setContentsMargins(QMargins());
    toolBar->addSeparator();
    toolBar->addWidget(tabBarWidget);
    Qt::ToolBarArea toolbarArea = static_cast<Qt::ToolBarArea>(Config::value("toolbarArea", Qt::TopToolBarArea).toInt());
    if (toolbarArea != Qt::LeftToolBarArea
        && toolbarArea != Qt::RightToolBarArea
        && toolbarArea != Qt::TopToolBarArea
        && toolbarArea != Qt::BottomToolBarArea) {
        toolbarArea = Qt::TopToolBarArea;
    }
    addToolBar(toolbarArea, toolBar);

    stackedWidget = new QStackedWidget();
    for (PageWidget *pageWidget : pageWidgets)
        stackedWidget->addWidget(pageWidget);

    QWidget *tempW = new QWidget();
    QGridLayout *mainLayout = new QGridLayout(tempW);
    mainLayout->addWidget(list1, 0, 0);
    mainLayout->addWidget(lineSearch, 1, 0);
    mainLayout->addWidget(bgPreview, 2, 0);
    mainLayout->addWidget(stackedWidget, 0, 1, 3, 1);
    mainLayout->setColumnStretch(1, 1);

    mainStackedWidget = new QStackedWidget(this);
    mainStackedWidget->addWidget(tempW);

    setCentralWidget(mainStackedWidget);

    searchAllDialog = new SearchAll(this);
    searchDialog = new Search(list1, searchAllDialog, this);

    closeFiles();
    setCurrentPage(Config::value("currentPage", TextPage).toInt());

    connect(actionOpen, &QAction::triggered, this, [this]() {
        QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), "", tr("Fichiers compatibles (*.fs *.iso *.bin);;Archives FS (*.fs);;Fichiers Image Disque (*.iso *.bin)"));
        if (!path.isEmpty()) {
            this->openFile(path);
        }
    });
    connect(actionSaveAs, &QAction::triggered, this, [this]() {
        QString path = fieldArchive != nullptr ? fieldArchive->archivePath() : field->getArchiveHeader()->path();
        this->saveAs(path);
    });
    connect(searchDialog, &Search::foundText, this, &MainWindow::gotoText);
    connect(searchDialog, &Search::foundOpcode, this, &MainWindow::gotoScript);
    connect(searchAllDialog, &SearchAll::foundText, this, &MainWindow::gotoText);
    connect(searchAllDialog, &SearchAll::foundOpcode, this, &MainWindow::gotoScript);
    connect(lineSearch, &QLineEdit::textEdited, this, &MainWindow::filterMap);
    connect(lineSearch, &QLineEdit::returnPressed, this, &MainWindow::filterMap);
    connect(this, &MainWindow::fieldIdChanged, searchDialog, &Search::setFieldId);
    connect(list1, &QTreeWidget::itemSelectionChanged, this, &MainWindow::fillPage);
    connect(tabBar, &QTabBar::currentChanged, this, &MainWindow::setCurrentPage);
    for (PageWidget *pageWidget : pageWidgets)
      connect(pageWidget, &PageWidget::modified, this, [this]() {
          this->setModified(false);  // Or true, depending on your logic
      });
    connect(bgPreview, &BGPreview::triggered, this, &MainWindow::bgPage);
    connect(fieldThread, &FieldThread::background, this, &MainWindow::fillBackground);
}

void MainWindow::showEvent(QShowEvent *)
{
	if(firstShow) {
		if(!windowState().testFlag(Qt::WindowMaximized)) {
      QScreen *screen = QGuiApplication::primaryScreen();
      QPoint screenCenter = screen->geometry().center();
			move(screenCenter.x() - width()/2, screenCenter.y() - height()/2);
		}
		toolBar->setVisible(Config::value("toolbarVisible", true).toBool());
	}
	firstShow = false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if(closeFiles(true)==2)		event->ignore();
	else {
		Config::setValue("mainWindowMaximized", windowState().testFlag(Qt::WindowMaximized));
		if(!windowState().testFlag(Qt::WindowMaximized))
			Config::setValue("mainWindowSize", size());
		Config::setValue("toolbarArea", toolBarArea(toolBar));
		Config::setValue("toolbarVisible", toolBar->isVisible());
		Config::setValue("list1ColumnSort", list1->sortColumn());
		Config::setValue("currentPage", stackedWidget->currentIndex());
		if(!FF8Font::saveFonts()) {
			QMessageBox::critical(nullptr, QObject::tr("Enregistrement des données"), QObject::tr("Les polices de caractères n'ont pas pu être enregistrées !"));
		}
		event->accept();
	}
}

void MainWindow::fullScreen()
{
	if(isFullScreen())	showNormal();
	else				showFullScreen();
}

void MainWindow::setGameLang(QAction *action)
{
	QString path;

	Config::setValue("gameLang", action->text());

	if(fieldArchive != nullptr && actionOpti->isEnabled()) {
		path = ((FieldArchivePC *)fieldArchive)->getFsArchive()->path();
	} else if(field != nullptr) {
		path = field->path();
	}

	closeFiles();
	openFsArchive(path);
}

void MainWindow::filterMap()
{
	QList<QTreeWidgetItem *> items = list1->findItems(lineSearch->text(), Qt::MatchStartsWith);
	if(!items.isEmpty())
		list1->scrollToItem(items.first(), QAbstractItemView::PositionAtTop);
}

bool MainWindow::openArchive(const QString &path)
{
	searchDialog->setFieldArchive(fieldArchive);
	searchAllDialog->setFieldArchive(fieldArchive);
	if(_varManager != nullptr)
		_varManager->setFieldArchive(fieldArchive);

	ProgressWidget progress(tr("Ouverture..."), ProgressWidget::Cancel, this);

  QElapsedTimer t; 
  t.start();

	int error = fieldArchive->open(path, &progress);

  qDebug() << "openTime" << t.elapsed() << "ms";

	TextPreview::reloadFont();

	setReadOnly(fieldArchive->isReadOnly());
	if(error == 0) {
		QList<QTreeWidgetItem *> items;

		int fieldID=0;
		foreach(Field *field, fieldArchive->getFields()) {
			QString desc;
			if(field->hasJsmFile())
				desc = Data::location(field->getJsmFile()->mapID());
			else
				desc = QString();

			int index = fieldArchive->mapList().indexOf(field->name());
			QString mapId = index==-1 ? "~" : QString("%1").arg(index, 3, 10, QChar('0'));

			QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << field->name() << desc << mapId);
//			maplistcpy.removeOne(field->name());

			if(!field->hasFiles())
				item->setFlags(Qt::NoItemFlags);
			item->setData(0, Qt::UserRole, fieldID++);
			item->setForeground(1, QColor(0x5b,0x6b,0xa7));

			items.append(item);
		}

		list1->setEnabled(true);
		lineSearch->setEnabled(true);
		bgPreview->setEnabled(true);
		list1->addTopLevelItems(items);
		list1->resizeColumnToContents(0);
		list1->resizeColumnToContents(1);
		list1->resizeColumnToContents(2);

		actionExport->setEnabled(true);
		menuExportAll->setEnabled(true);

		((CharaWidget *)pageWidgets.at(ModelPage))->setMainModels(fieldArchive->getModels());
		((JsmWidget *)pageWidgets.at(ScriptPage))->setMainModels(fieldArchive->getModels());
		((JsmWidget *)pageWidgets.at(ScriptPage))->setFieldArchive(fieldArchive);

		QString previousSessionField = Config::value("currentField").toString();
		if(!previousSessionField.isEmpty()) {
			items = list1->findItems(previousSessionField, Qt::MatchExactly);
			if(!items.isEmpty())	list1->setCurrentItem(items.first());
			else					list1->setCurrentItem(list1->topLevelItem(0));
		} else		list1->setCurrentItem(list1->topLevelItem(0));

		list1->setFocus();
		return true;
	} else if(error != 2 && error != 3) {
		QMessageBox::warning(this, tr("Erreur d'ouverture"), fieldArchive->errorMessage());
	}

	return false;
}

bool MainWindow::openFsArchive(const QString &path)
{
//	qDebug() << QString("MainWindow::openFsArchive(%1)").arg(path);

	FieldArchivePC *fieldArchivePc = new FieldArchivePC();
	fieldArchive = fieldArchivePc;
	openArchive(path);

	if(fieldArchive->nbFields() > 0) {
		actionOpti->setEnabled(true);
		actionSaveAs->setEnabled(true);
		buildGameLangMenu(fieldArchivePc->languages());
	} else {
		field = new FieldPC(path, Config::value("gameLang", "en").toString());
		if(field->hasFiles()) {
			delete fieldArchive;
			fieldArchive = nullptr;
			list1->setEnabled(false);
			lineSearch->setEnabled(false);
			bgPreview->setEnabled(true);
			buildGameLangMenu(field->languages());
			fillPage();
		} else {
			delete field;
			field = nullptr;
			manageArchive();
			actionSaveAs->setEnabled(false);
		}
	}

	tabBar->setTabEnabled(tabBar->count()-1, true);

	return true;
}

bool MainWindow::openMsdFile(const QString &)
{
//	qDebug() << QString("MainWindow::openMsdFile(%1)").arg(path);

	return false;

//	file = new MsdFile();
//	if(!file->open(path)) {
//		QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier\n'%1'\nMessage d'erreur :\n%2").arg(path, file->lastError));
//		delete file;
//		file = 0;
//		return false;
//	}

//	list1->setEnabled(false);
//	lineSearch->setEnabled(false);
//	pageWidgets.at(TextPage)->setData(file);
//	pageWidgets.at(TextPage)->setFocus();
//	setCurrentPage(TextPage);

//	return true;
}

bool MainWindow::openJsmFile(const QString &)
{
//	qDebug() << QString("MainWindow::openJsmFile(%1)").arg(path);

	return false;

//	jsmFile = new JsmFile();
//	if(!jsmFile->open(path)) {
//		QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier\n'%1'\nMessage d'erreur :\n%2").arg(path, jsmFile->lastError));
//		delete jsmFile;
//		jsmFile = NULL;
//		return false;
//	}
//	list1->setEnabled(false);
//	lineSearch->setEnabled(false);
////	pageWidgets.at(ScriptPage)->setData(jsmFile);//TODO
//	pageWidgets.at(ScriptPage)->setFocus();
//	setCurrentPage(ScriptPage);

//	return false;
}

void MainWindow::setReadOnly(bool readOnly)
{
	foreach(PageWidget *pageWidget, pageWidgets)
		pageWidget->setReadOnly(readOnly);

	actionImport->setDisabled(readOnly);
}

void MainWindow::buildGameLangMenu(const QStringList &langs)
{
	if(!menuGameLang) {
		menuGameLang = new QMenu();
		actionGameLang->setMenu(menuGameLang);
		connect(menuGameLang, SIGNAL(triggered(QAction*)), SLOT(setGameLang(QAction*)));
	}

	actionGameLang->setVisible(!langs.empty());
	menuGameLang->clear();

	QString currentLang = Config::value("gameLang", "en").toString();

	foreach(const QString &lang, langs) {
		QAction *action = menuGameLang->addAction(lang);
		action->setCheckable(true);
		action->setChecked(lang == currentLang);
	}
}

bool MainWindow::openIsoArchive(const QString &path)
{
//	qDebug() << QString("MainWindow::openIsoArchive(%1)").arg(path);
	fieldArchive = new FieldArchivePS();
	return openArchive(path);
}

void MainWindow::fillPage()
{
	if(tabBar->currentIndex() >= tabBar->count()-1)
		return;

	bgPreview->clear();

	QElapsedTimer t;t.start();

	if(this->field != nullptr) {
		currentField = this->field;

		this->field->open2();
	} else {
		QTreeWidgetItem *item = list1->currentItem();
		if(item==nullptr)	return;
		list1->scrollToItem(item);
		if(fieldArchive==nullptr)	return;

		int fieldID = item->data(0, Qt::UserRole).toInt();
		currentField = fieldArchive->getField(fieldID);
		if(currentField == nullptr)	return;

		emit fieldIdChanged(fieldID);

		fieldArchive->openBG(currentField);
		/*if(fieldThread->isRunning()) {
			qDebug() << "exit thread";
			fieldThread->exit(0);
		}
		qDebug() << "setData thread";
		fieldThread->setData(fieldArchive, currentField);
		qDebug() << "start thread";
		fieldThread->start();*/
	}

	foreach(PageWidget *pageWidget, pageWidgets)
		pageWidget->setData(currentField);

	if(currentField->hasBackgroundFile())
		bgPreview->fill(QPixmap::fromImage(currentField->getBackgroundFile()->background()));
	else
		bgPreview->fill(FF8Image::errorPixmap());

//	qDebug() << "BG" << t.elapsed();

	pageWidgets.at(tabBar->currentIndex())->fill();
}

void MainWindow::fillBackground(const QImage &image)
{
	bgPreview->fill(QPixmap::fromImage(image));
}

void MainWindow::setModified(bool modified)
{
	if(modified && (!fieldArchive || fieldArchive->isReadOnly()) && (!field || !field->isOpen()))
		return;

	actionSave->setEnabled(modified);
	setWindowModified(modified);

	if(modified) {
		if(list1->selectedItems().size()>0)
			list1->selectedItems().first()->setForeground(0, QColor(0xd1,0x1d,0x1d));
	} else {
		for(int i=0 ; i<list1->topLevelItemCount() ; ++i)
			if(list1->topLevelItem(i)->foreground(0).color()==qRgb(0xd1,0x1d,0x1d))
				list1->topLevelItem(i)->setForeground(0, QColor(0x1d,0xd1,0x1d));
	}
}

int MainWindow::closeFiles(bool quit)
{
	//qDebug() << "MainWindow::closeFiles()";

	if(list1->currentItem() != nullptr)
		Config::setValue("currentField", list1->currentItem()->text(0));

	if(actionSave->isEnabled() && fieldArchive!=nullptr)
	{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Sauvegarder"));
    msgBox.setText(tr("Voulez-vous enregistrer les changements de %1 ?").arg(fieldArchive->archivePath()));
    QPushButton *yesButton = msgBox.addButton(tr("Oui"), QMessageBox::YesRole);
    QPushButton *noButton = msgBox.addButton(tr("Non"), QMessageBox::NoRole);
    msgBox.addButton(tr("Annuler"), QMessageBox::RejectRole);

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();

    int reponse;
    if (msgBox.clickedButton() == yesButton) {
        reponse = QMessageBox::YesRole;
    } else if (msgBox.clickedButton() == noButton) {
        reponse = QMessageBox::NoRole;
    } else {
        reponse = QMessageBox::RejectRole;
    }
		if(reponse == 0)				save();
		if(quit || reponse == 2)	return reponse;
	}

	if(quit)	return 0;

	list1->setEnabled(false);
	lineSearch->setEnabled(false);
	list1->clear();
	setModified(false);
	actionSaveAs->setEnabled(false);
	actionExport->setEnabled(false);
	menuExportAll->setEnabled(false);
	actionImport->setEnabled(false);
	actionOpti->setEnabled(false);
	tabBar->setTabEnabled(tabBar->count()-1, false);
	actionClose->setEnabled(false);
	bgPreview->clear();
	bgPreview->setEnabled(false);
	actionGameLang->setVisible(false);
	foreach(PageWidget *pageWidget, pageWidgets) {
		pageWidget->clear();
		pageWidget->cleanData();
	}
	((CharaWidget *)pageWidgets.at(ModelPage))->setMainModels(nullptr);
	((JsmWidget *)pageWidgets.at(ScriptPage))->setMainModels(nullptr);
	currentPath->setText(QString());
	setReadOnly(false);

	searchDialog->setFieldArchive(nullptr);
	searchAllDialog->setFieldArchive(nullptr);
	if(_varManager != nullptr)		_varManager->setFieldArchive(nullptr);

	if(fsDialog) {
		mainStackedWidget->removeWidget(fsDialog);
		fsDialog->deleteLater();
		fsDialog = nullptr;
	}

	currentField = nullptr;

	if(fieldArchive!=nullptr) {
		delete fieldArchive;
		fieldArchive = nullptr;
		field = nullptr;
	}
	if(field!=nullptr) {
		delete field;
		field = nullptr;
	}

	setWindowTitle("[*]"%PROG_FULLNAME);

	return 0;
}

void MainWindow::openFile(QString path)
{
	if(path.isEmpty())
	{
		path = Config::value("open_path").toString();
		if(path.isEmpty()) {
			path = Data::AppPath();
			if(!path.isEmpty())
				path.append("/Data");
		}

		path = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), path, tr("Fichiers compatibles (*.fs *.iso *.bin);;Archives FS (*.fs);;Fichiers Image Disque (*.iso *.bin)"));
	}

	if(!path.isEmpty())
	{
		int index;
		if((index = path.lastIndexOf('/')) == -1)
			index = path.size();
		Config::setValue("open_path", path.left(index));

		closeFiles();

		QString ext = path.mid(path.lastIndexOf('.')+1).toLower();
		bool ok = false;
		if(ext == "fs")
			ok = openFsArchive(path);
//		else if(ext == "msd")
//			ok = openMsdFile(path);
//		else if(ext == "jsm")
//			ok = openJsmFile(path);
		else if(ext == "iso" || ext == "bin")
			ok = openIsoArchive(path);

		if(ok) {
			setWindowTitle(QString("[*]%1 - %2").arg(path.mid(path.lastIndexOf('/')+1), PROG_FULLNAME));
			currentPath->setText(path);
			actionClose->setEnabled(true);
		}
	}
}

void MainWindow::save()
{
	if(fieldArchive == nullptr && (field == nullptr || !field->isOpen()))	return;

	saveAs(fieldArchive != nullptr ? fieldArchive->archivePath() : field->getArchiveHeader()->path());
}

void MainWindow::saveAs(QString path)
{
	if(fieldArchive == nullptr && (field == nullptr || !field->isOpen()))	return;

	/* int errorFieldID, errorGroupID, errorMethodID, errorLine;
	QString errorStr;

	if(!fieldArchive->compileScripts(errorFieldID, errorGroupID, errorMethodID, errorLine, errorStr)) {
		QMessageBox::warning(this, tr("Erreur de compilation"), tr("Écran %1 (%2), groupe %3, méthode %4, ligne %5 :\n%6.")
							 .arg(fieldArchive->getField(errorFieldID)->name())
							 .arg(errorFieldID)
							 .arg(errorGroupID)
							 .arg(errorMethodID)
							 .arg(errorLine)
							 .arg(errorStr));
		gotoScript(errorFieldID, errorGroupID, errorMethodID, errorLine);
		return;
	}*/

	if(path.isEmpty())
	{
		path = fieldArchive != nullptr ? fieldArchive->archivePath() : field->getArchiveHeader()->path();
		path = QFileDialog::getSaveFileName(this, tr("Enregistrer Sous"), path, tr("Archive FS (*.fs)"));
		if(path.isNull())		return;
	}

	bool ok = true;

	if(fieldArchive != nullptr) {
		ProgressWidget progress(tr("Enregistrement..."), ProgressWidget::Cancel, this);

		ok = ((FieldArchivePC *)fieldArchive)->save(&progress, path);
	} else {
		ok = field->save(path);
		field->setModified(false);
	}

	if(ok) {
		setModified(false);
		currentPath->setText(path);
		setWindowTitle(QString("[*]%1 - %2").arg(path.mid(path.lastIndexOf('/')+1), PROG_FULLNAME));
	} else {
		QMessageBox::warning(this, tr("Erreur"), tr("Une erreur s'est produite lors de l'enregistrement."));
	}
}

void MainWindow::exportCurrent()
{
    if(!currentField)	return;

	QString path = fieldArchive != nullptr ? fieldArchive->archivePath() : field->path();
	QStringList filter;
	QList<int> typeList;

	/*if(currentField->hasPvpFile()
			&& currentField->hasBackgroundFile()
			&& currentField->hasTdwFile()) {
		filter.append(tr("Fichier données écran PlayStation (*.MIM)"));
		typeList.append(MIM);
	}
	if(currentField->hasInfFile()
			&& currentField->hasCaFile()
			&& currentField->hasIdFile()
			&& currentField->hasBackgroundFile()) {
		filter.append(tr("Fichier informations écran PlayStation (*.MAP)"));
		typeList.append(MAP);
	}
	if(currentField->hasCharaFile()) {
		filter.append(tr("Fichier modèles 3D écran PlayStation (*.LZK)"));
		typeList.append(LZK);
		filter.append(tr("Fichier modèles 3D écran PC (*.one)"));
		typeList.append(one);
	}
	if(currentField->hasBackgroundFile()) {
		filter.append(tr("Fichier données décors écran PC (*.mim)"));
		typeList.append(mim);
		filter.append(tr("Fichier informations décors écran PC (*.map)"));
		typeList.append(map);
	}*/
	for(int i=0 ; i<FILE_COUNT ; ++i) {
		if(i == Field::Jsm) {
			if(currentField->hasJsmFile()) {
				filter.append(currentField->getJsmFile()->filterText());
				typeList.append(i);
				if(currentField->getJsmFile()->hasSym()) {
					filter.append(tr("Fichier nom des scripts écran PC (*.sym)"));
					typeList.append(FILE_COUNT);
				}
			}
		}
		else {
			if(currentField->hasFile(Field::FileType(i))) {
				filter.append(currentField->getFile(Field::FileType(i))->filterText());
				typeList.append(i);
			}
		}
	}

	if(filter.isEmpty()) {
		QMessageBox::warning(this, tr("Erreur"), tr("Cet écran ne contient pas assez d'éléments pour être exporté."));
		return;
	}

	QString selectedFilter;
	path = QFileDialog::getSaveFileName(this, tr("Exporter"), path, filter.join(";;"), &selectedFilter);
	if(path.isNull())		return;
	
	int type = typeList.at(filter.indexOf(selectedFilter));

	switch(type) {
	case FILE_COUNT:
		if(!currentField->getJsmFile()->toFileSym(path)) {
			QMessageBox::warning(this, tr("Erreur"), currentField->getJsmFile()->errorString());
		}
		break;
	default:
		if(!currentField->getFile(Field::FileType(type))->toFile(path)) {
			QMessageBox::warning(this, tr("Erreur"), currentField->getFile(Field::FileType(type))->errorString());
		}
	}
}

void MainWindow::exportAllScripts()
{
	if(!fieldArchive)	return;

	QString oldPath = Config::value("export_path").toString();

	QString dirPath = QFileDialog::getExistingDirectory(this, tr("Exporter"), oldPath);
	if (dirPath.isNull()) {
		return;
	}

	Config::setValue("export_path", dirPath);

	ProgressWidget progress(tr("Export..."), ProgressWidget::Cancel, this);

	ScriptExporter exporter(fieldArchive);

	if (!exporter.toDir(dirPath, &progress) && !progress.observerWasCanceled()) {
		QMessageBox::warning(this, tr("Erreur"), exporter.errorString());
	}
}

void MainWindow::exportAllEncounters()
{
	if(!fieldArchive)	return;

	QString oldPath = Config::value("export_path").toString();

	QString dirPath = QFileDialog::getExistingDirectory(this, tr("Exporter"), oldPath);
	if (dirPath.isNull()) {
		return;
	}

	Config::setValue("export_path", dirPath);

	ProgressWidget progress(tr("Export..."), ProgressWidget::Cancel, this);

	EncounterExporter exporter(fieldArchive);

	if (!exporter.toDir(dirPath, &progress) && !progress.observerWasCanceled()) {
		QMessageBox::warning(this, tr("Erreur"), exporter.errorString());
	}
}

void MainWindow::exportAllBackground()
{
	if(!fieldArchive)	return;

	QString oldPath = Config::value("export_path").toString();

	QString dirPath = QFileDialog::getExistingDirectory(this, tr("Exporter"), oldPath);
	if (dirPath.isNull()) {
		return;
	}

	Config::setValue("export_path", dirPath);

	ProgressWidget progress(tr("Export..."), ProgressWidget::Cancel, this);

	BackgroundExporter exporter(fieldArchive);

	if (!exporter.toDir(dirPath, &progress) && !progress.observerWasCanceled()) {
		QMessageBox::warning(this, tr("Erreur"), exporter.errorString());
	}
}

void MainWindow::importCurrent()
{
    if(!currentField)	return;

	QString path = fieldArchive != nullptr ? fieldArchive->archivePath() : field->path();
    QStringList filter;
    QList<int> typeList;

    for(int i=0 ; i<FILE_COUNT ; ++i) {
        if(i != Field::Background && i != Field::Jsm) {
			if(currentField->hasFile(Field::FileType(i))) {
				filter.append(currentField->getFile(Field::FileType(i))->filterText());
                typeList.append(i);
            }
        }
    }

    if(filter.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Cet écran ne contient pas assez d'éléments pour être importé."));
        return;
    }

    QString selectedFilter;
    path = QFileDialog::getSaveFileName(this, tr("Importer"), path, filter.join(";;"), &selectedFilter);
    if(path.isNull())		return;

	if(!currentField->getFile(Field::FileType(typeList.at(filter.indexOf(selectedFilter))))->fromFile(path)) {
		QMessageBox::warning(this, tr("Erreur"), currentField->getFile(Field::FileType(typeList.at(filter.indexOf(selectedFilter))))->errorString());
    }
}

void MainWindow::optimizeArchive()
{
  QMessageBox msgBox(this);
  msgBox.setWindowTitle(tr("À propos de l'optimisation"));
  msgBox.setText(tr("L'optimiseur d'archive va modifier l'ordre des fichiers pour permettre une ouverture bien plus rapide avec Deling.\nIl est vivement conseillé de sauvegarder l'archive (fs, fi et fl) avant de continuer."));
  QPushButton *optimizeButton = msgBox.addButton(tr("Lancer l'optimisation !"), QMessageBox::AcceptRole);
  QPushButton *cancelButton = msgBox.addButton(tr("Annuler"), QMessageBox::RejectRole);

  msgBox.setIcon(QMessageBox::Information);
  msgBox.exec();

  int reponse = -1;
  if (msgBox.clickedButton() == optimizeButton) {
      reponse = QMessageBox::AcceptRole;
  } else if (msgBox.clickedButton() == cancelButton) {
      reponse = QMessageBox::RejectRole;
  }
	if(reponse!=0)	return;

	ProgressWidget progress(tr("Optimisation..."), ProgressWidget::Cancel, this);

	((FieldArchivePC *)fieldArchive)->optimiseArchive(&progress);
}

void MainWindow::manageArchive()
{
	setCurrentPage(stackedWidget->count());
}

void MainWindow::search()
{
	searchDialog->setSearchText(((MsdWidget *)pageWidgets.at(TextPage))->selectedText());
	searchDialog->setSearchOpcode(((JsmWidget *)pageWidgets.at(ScriptPage))->selectedOpcode());
	searchDialog->show();
	searchDialog->raise();
	searchDialog->activateWindow();
	searchDialog->setFocus();
}

void MainWindow::varManager()
{
	if(_varManager == nullptr)
		_varManager = new VarManager(fieldArchive, this);
	_varManager->show();
	_varManager->raise();
	_varManager->activateWindow();
}

void MainWindow::configDialog()
{
	ConfigDialog dialog(this);
	dialog.addAction(actionRun);
	if(dialog.exec() == QDialog::Accepted) {
		((MsdWidget *)pageWidgets.at(TextPage))->updateText();
	}
}

void MainWindow::runFF8()
{
	if(!QProcess::startDetached("\"" % Data::AppPath() % "/FF8.exe\"", QStringList(), Data::AppPath())) {
		QMessageBox::warning(this, tr("Erreur"), tr("Final Fantasy VIII n'a pas pu être lancé.\n%1").arg(Data::AppPath() % "/FF8.exe"));
	}
}

void MainWindow::miscSearch()
{
	miscSearchD = new MiscSearch(fieldArchive, this);
	miscSearchD->show();
}

void MainWindow::bgPage()
{
	setCurrentPage(BackgroundPage);
}

void MainWindow::setCurrentPage(int index)
{
	//qDebug() << QString("MainWindow::setCurrentPage(%1)").arg(index);

	tabBar->blockSignals(true);
	if(tabBar->currentIndex() != index)
		tabBar->setCurrentIndex(index);
	tabBar->blockSignals(false);

	if(index >= stackedWidget->count()) {
		FsArchive *fsArchive;
		if(fieldArchive) {
			fsArchive = ((FieldArchivePC *)fieldArchive)->getFsArchive();
		} else if(field) {
			fsArchive = field->getArchiveHeader();
		} else {
			return;
		}
		QString path;

		if(fsDialog) {
			path = fsDialog->getCurrentPath();
			mainStackedWidget->removeWidget(fsDialog);
			fsDialog->deleteLater();
		}
		mainStackedWidget->addWidget(fsDialog = new FsDialog(fsArchive, this));
		if(!path.isEmpty()) {
			fsDialog->setCurrentPath(path);
		}
		mainStackedWidget->setCurrentWidget(fsDialog);

		return;
	} else {
		mainStackedWidget->setCurrentIndex(0);
	}

	PageWidget *currentPage = pageWidgets.at(index);

	if(!currentPage->isFilled())
		currentPage->fill();

	searchDialog->setCurrentIndex(index);
	stackedWidget->setCurrentIndex(index);
}

bool MainWindow::gotoField(int fieldID)
{
	int i, size=list1->topLevelItemCount();

	for(i=0 ; i<size ; ++i) {
		QTreeWidgetItem *item = list1->topLevelItem(i);
		if(item->data(0, Qt::UserRole).toInt() == fieldID) {
			blockSignals(true);
			list1->setCurrentItem(item);
			list1->scrollToItem(item);
			blockSignals(false);
			return true;
		}
	}
	return false;
}

void MainWindow::gotoText(int fieldID, int textID, int from, int size)
{
	MsdWidget *msd = (MsdWidget *)pageWidgets.at(TextPage);
	msd->blockSignals(true);
	if(tabBar->currentIndex() != TextPage)
		setCurrentPage(TextPage);

	if(gotoField(fieldID)) {
		msd->gotoText(textID, from, size);
	}
	msd->blockSignals(false);
}

void MainWindow::gotoScript(int fieldID, int groupID, int methodID, int opcodeID)
{
	if(tabBar->currentIndex()!=ScriptPage)
		setCurrentPage(ScriptPage);
//	qDebug() << "gotoScript" << fieldID << groupID << methodID << opcodeID;
	if(gotoField(fieldID)) {
		((JsmWidget *)pageWidgets.at(ScriptPage))->gotoScript(groupID, methodID, opcodeID);
	}
}

void MainWindow::about()
{
	AboutDialog about(this);
	about.exec();
}
