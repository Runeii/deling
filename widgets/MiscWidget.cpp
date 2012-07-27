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
#include "widgets/MiscWidget.h"

MiscWidget::MiscWidget(QWidget *parent)
	: PageWidget(parent)
{
}

void MiscWidget::build()
{
	if(isBuilded())	return;

	QLabel *nameLbl = new QLabel(tr("Nom :"), this);
	nameEdit = new QLineEdit(this);
    nameEdit->setMaxLength(8);
	QLabel *pmpLbl = new QLabel(tr("PMP :"), this);
	pmpEdit = new QLineEdit(this);
	QLabel *pmdLbl = new QLabel(tr("PMD :"), this);
	pmdEdit = new QLineEdit(this);
	QLabel *pvpLbl = new QLabel(tr("PVP :"), this);
	pvpEdit = new QDoubleSpinBox(this);
	pvpEdit->setDecimals(0);
	pvpEdit->setRange(0, (quint32)-1);

	connect(nameEdit, SIGNAL(textEdited(QString)), SLOT(editName(QString)));
	connect(pmpEdit, SIGNAL(textEdited(QString)), SLOT(editPmp(QString)));
	connect(pmdEdit, SIGNAL(textEdited(QString)), SLOT(editPmd(QString)));
	connect(pvpEdit, SIGNAL(valueChanged(double)), SLOT(editPvp(double)));

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(nameLbl, 0, 0);
	layout->addWidget(nameEdit, 0, 1);
	layout->addWidget(pmpLbl, 1, 0);
	layout->addWidget(pmpEdit, 1, 1);
	layout->addWidget(pmdLbl, 2, 0);
	layout->addWidget(pmdEdit, 2, 1);
	layout->addWidget(pvpLbl, 3, 0);
	layout->addWidget(pvpEdit, 3, 1);
	layout->setRowStretch(4, 1);
	layout->setColumnStretch(1, 1);
	layout->setContentsMargins(QMargins());

	PageWidget::build();
}

void MiscWidget::clear()
{
	if(!isFilled())	return;

	nameEdit->clear();
	pmpEdit->clear();
	pmdEdit->clear();
	pvpEdit->clear();

	PageWidget::clear();
}

void MiscWidget::setReadOnly(bool readOnly)
{
	if(isBuilded()) {
		nameEdit->setReadOnly(readOnly);
		pmpEdit->setReadOnly(readOnly);
		pmdEdit->setReadOnly(readOnly);
		pvpEdit->setReadOnly(readOnly);
	}

	PageWidget::setReadOnly(readOnly);
}

void MiscWidget::fill()
{
	if(!isBuilded())	build();
	if(isFilled())		clear();

	if(!hasData() || (!data()->hasPmpFile() && !data()->hasPmdFile()
					  && !data()->hasPvpFile() && !data()->hasInfFile()))	return;

    if(data()->hasInfFile()) {
        nameEdit->setText(data()->getInfFile()->getMapName());
    }
	nameEdit->setEnabled(data()->hasInfFile());

	if(data()->hasPmpFile()) {
		pmpEdit->setText(data()->getPmpFile()->getPmpData().toHex());
    }
	pmpEdit->setEnabled(data()->hasPmpFile());

	if(data()->hasPmdFile()) {
		pmdEdit->setText(data()->getPmdFile()->getPmdData().toHex());
	}
	pmdEdit->setEnabled(data()->hasPmdFile());

	if(data()->hasPvpFile()) {
		pvpEdit->setValue(data()->getPvpFile()->value());
	}
	pvpEdit->setEnabled(data()->hasPvpFile());

	PageWidget::fill();
}

void MiscWidget::editName(const QString &name)
{
	if(data()->hasInfFile()) {
		data()->getInfFile()->setMapName(name);
		emit modified();
	}
}

void MiscWidget::editPmp(const QString &pmp)
{
	if(data()->hasPmpFile()) {
		data()->getPmpFile()->setPmpData(
					QByteArray::fromHex(pmp.toLatin1())
					.leftJustified(data()->getPmpFile()->getPmpData().size(), '\x00', true));
		emit modified();
		pmpEdit->setText(data()->getPmpFile()->getPmpData().toHex());
	}
}

void MiscWidget::editPmd(const QString &pmd)
{
	if(data()->hasPmdFile()) {
		data()->getPmdFile()->setPmdData(
					QByteArray::fromHex(pmd.toLatin1())
					.leftJustified(data()->getPmdFile()->getPmdData().size(), '\x00', true));
		emit modified();
		pmdEdit->setText(data()->getPmdFile()->getPmdData().toHex());
	}
}

void MiscWidget::editPvp(double value)
{
	if(data()->hasPvpFile()) {
		if(data()->getPvpFile()->value() != value) {
			data()->getPvpFile()->setValue(value);
			emit modified();
		}
	}
}
