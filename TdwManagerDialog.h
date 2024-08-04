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
#ifndef TDWMANAGERDIALOG_H
#define TDWMANAGERDIALOG_H

#include <QtWidgets>
#include "widgets/TdwWidget2.h"
#include "Listwidget.h"

class TdwManagerDialog : public QDialog
{
	Q_OBJECT
public:
	explicit TdwManagerDialog(QWidget *parent=0);
private slots:
	void setTdw(int id);
	void addFont();
	void removeFont();
private:
	void fillList1();
	bool newNameDialog(QString &name, QString &nameId);
	QToolBar *toolbar1;
	QAction *plusAction, *minusAction;
	QListWidget *list1;
	TdwWidget2 *tdwWidget;
};

#endif // TDWMANAGERDIALOG_H
