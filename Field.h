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
#ifndef FIELD_H
#define FIELD_H

#include <QtCore>
#include "files/MsdFile.h"
#include "files/JsmFile.h"
#include "files/WalkmeshFile.h"
#include "files/InfFile.h"
#include "files/MiscFile.h"
#include "files/EncounterFile.h"
#include "files/BackgroundFile.h"
#include "files/TdwFile.h"
#include "files/CharaFile.h"
#include "files/MskFile.h"

class Field
{
public:
	Field(const QString &name);
	virtual ~Field();

	bool isOpen() const;
	void setOpen(bool open);

	void openMsdFile(const QByteArray &msd);
	void openJsmFile(const QByteArray &jsm, const QByteArray &sym=QByteArray());
	void openWalkmeshFile(const QByteArray &id, const QByteArray &ca=QByteArray());
	void openEncounterFile(const QByteArray &rat, const QByteArray &mrt);
    void openInfFile(const QByteArray &inf);
    void openMiscFile(const QByteArray &pmp, const QByteArray &pmd, const QByteArray &pvp);
	void openBackgroundFile(const QByteArray &map, const QByteArray &mim);
	void openTdwFile(const QByteArray &tdw);
	void openCharaFile(const QByteArray &one, bool ps);
	void openMskFile(const QByteArray &msk);

	bool hasMsdFile() const;
	bool hasJsmFile() const;
	bool hasWalkmeshFile() const;
	bool hasEncounterFile() const;
    bool hasInfFile() const;
	bool hasMiscFile() const;
	bool hasBackgroundFile() const;
	bool hasTdwFile() const;
	bool hasCharaFile() const;
	bool hasMskFile() const;

	virtual bool hasMapMimFiles() const=0;
	bool hasFiles() const;

	MsdFile *getMsdFile() const;
	JsmFile *getJsmFile() const;
	WalkmeshFile *getWalkmeshFile() const;
	EncounterFile *getEncounterFile() const;
    InfFile *getInfFile() const;
	MiscFile *getMiscFile() const;
	BackgroundFile *getBackgroundFile() const;
	TdwFile *getTdwFile() const;
	CharaFile *getCharaFile() const;
	MskFile *getMskFile() const;

	bool isModified() const;
	const QString &name() const;

protected:
	void deleteMsdFile();
	void deleteJsmFile();
	void deleteWalkmeshFile();
	void deleteEncounterFile();
    void deleteInfFile();
	void deleteMiscFile();
	void deleteBackgroundFile();
	void deleteTdwFile();
	void deleteCharaFile();
	void deleteMskFile();

	bool _isOpen;
	QString _name;
	MsdFile *msdFile;
	JsmFile *jsmFile;
	WalkmeshFile *walkmeshFile;
	EncounterFile *encounterFile;
    InfFile *infFile;
	MiscFile *miscFile;
	BackgroundFile *backgroundFile;
	TdwFile *tdwFile;
	static CharaFile *charaFile;
	MskFile *mskFile;
};

#endif // FIELD_H
