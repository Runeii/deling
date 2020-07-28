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
#ifndef AKAOLISTFILE_H
#define AKAOLISTFILE_H

#include "files/File.h"

class AkaoListFile : public File
{
public:
	AkaoListFile();
	bool open(const QByteArray &akao);
	bool save(QByteArray &akao);
	inline QString filterText() const {
		return QString();
	}
	int akaoCount() const;
	const QByteArray &akao(int id) const;
	bool setAkao(int id, const QByteArray &akao);
	bool insertAkao(int id, const QByteArray &akao);
	void removeAkao(int id);
	QString parseScripts(int id, bool *warnings) const;
	int akaoID(int id) const;
	void setAkaoID(int id, quint16 akaoID);
private:
	QList<QByteArray> _akaos;
};

#endif // AKAOLISTFILE_H
