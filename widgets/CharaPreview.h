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
#ifndef CHARAPREVIEW_H
#define CHARAPREVIEW_H

#include <QtWidgets>
#include "CharaModel.h"
#include "BGPreview2.h"

class CharaPreview : public BGPreview2
{
	Q_OBJECT
public:
	explicit CharaPreview(QWidget *parent = nullptr);
	void fill(const QPixmap &background);
	void setMainModels(QHash<int, CharaModel *> *mainModels);
	void setModel(const CharaModel &model);
protected:
	inline bool hasHeightForWidth() const override {
		return true;
	}
	inline int heightForWidth(int w) const override {
		return w;
	}
private:
	QHash<int, CharaModel *> *mainModels;
};

#endif // CHARAPREVIEW_H
