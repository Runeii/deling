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
#include "CharaFile.h"

CharaFile::CharaFile() :
	File()
{
}

CharaFile::~CharaFile()
{
}

bool CharaFile::open(const QByteArray &one, bool ps)
{
	models.clear();

	if(one.size() < 0x800) {
		qWarning() << "CharaFile::open chara file too short" << one.size();
		return false;
	}

	quint32 count=0, offset, size, modelID, timOffset, modelOffset;
	const char *constData = one.constData();
	const char * const startData = constData;

	if(!ps) {
		memcpy(&count, constData, 4);
		constData += 4;
//		qDebug() << "count" << count;
	}

	for(quint32 i=0 ; (ps || i<count) && constData - startData < 0x800 ; ++i) {
		memcpy(&offset, constData, 4);
		constData += 4;
//		qDebug() << i << "offset" << QString::number(offset, 16);
		if(offset == 0) {
			break;
		}
		memcpy(&size, constData, 4);
		constData += 4;
//		qDebug() << "size" << size;

		memcpy(&modelID, constData, 4);
		constData += 4;

		if(modelID == size || ps) {
//			qDebug() << "size twice!";
			memcpy(&modelID, constData, 4);
			constData += 4;
		}

		if(modelID >> 24 == 0xd0) {
//			qDebug() << "modelID" << (modelID & 0xFFFF) << QString::number(modelID, 16);
			memcpy(&modelID, constData, 4);
			constData += 4;
//			qDebug() << "modelID²" << QString::number(modelID, 16);
			if(modelID == 0) {
				QString name;
				quint32 nextOffset;

				memcpy(&nextOffset, constData, 4);

				if (nextOffset != 0 && nextOffset != offset + size) { // Not testno format
					name = one.mid(constData - startData, 8);
//					qDebug() << name;
					constData += 8;
					memcpy(&modelID, constData, 4);
					constData += 4;
					if(modelID != 0xEEEEEEEE) {
						qWarning() << "CharaFile::open Unknown format (3)!" << i << QString::number(modelID, 16);
						return false;
					}
				}

				models.append(CharaModel(name));
			} else {
				qWarning() << "CharaFile::open Unknown format (2)!" << i << QString::number(modelID, 16);
				return false;
			}
		} else {
			QList<quint32> toc;

			if((modelID & 0xFFFFFF) == 0) {
				toc.append(0);
			}

			/*if(modelID >> 24 != 0 && modelID >> 24 != 0x10 && modelID >> 24 != 0x20) {
				qWarning() << "CharaFile::open Unknown format (4)!" << i << QString::number(modelID, 16);
			}*/
//			qDebug() << "tim offset" << QString::number(modelID & 0xFFFFFF, 16) << QString::number((modelID >> 24) & 0xFF, 16);
			do {
				memcpy(&timOffset, constData, 4);
				constData += 4;

				if(timOffset != 0xFFFFFFFF) {
					toc.append(timOffset);
				}
//				qDebug() << "tim offset" << QString::number(timOffset & 0xFFFFFF, 16) << QString::number((timOffset >> 24) & 0xFF, 16);
			} while(timOffset != 0xFFFFFFFF && constData - startData < 0x800);

			if(timOffset == 0xFFFFFFFF) {
				memcpy(&modelOffset, constData, 4);
				constData += 4;

				toc.append(modelOffset);
//				qDebug() << "model data offset" << QString::number(modelOffset, 16);

				toc.append(size);

				QString name;
				quint32 nextOffset;

				memcpy(&nextOffset, constData, 4);

				if (nextOffset != 0 && nextOffset != offset + size) { // Not testno format
					name = one.mid(constData - startData, 8);
	//				qDebug() << name;
					constData += 8;
					memcpy(&modelID, constData, 4);
					constData += 4;
					if(modelID != 0xEEEEEEEE) {
						//qWarning() << "CharaFile::open Unknown format (6)!" << i << QString::number(modelID, 16) << name << offset << toc;
	//					return false;
					}
				}

				if(!ps) {
					offset += 4;
				}

				QByteArray data = one.mid(offset, size);

				if(ps) {
					quint32 lzsSize=0;
					memcpy(&lzsSize, data.constData(), 4);
					if((quint32)data.size() < lzsSize + 4) {
						qWarning() << "CharaFile::open Compression error" << i << lzsSize << data.size();
						return false;
					}
					data = LZS::decompress(data.constData() + 4, lzsSize);
				}

				QList<TimFile> textures;

				// Toc = tim offsets + data offset + data size

				for(int i=0 ; i<toc.size()-2 ; ++i) {
					quint32 pos = toc.at(i) & 0xFFFFFF;
			//		qDebug() << "ouverture tim" << pos << ((toc.at(i+1) & 0xFFFFFF) - pos);
					textures.append(TimFile(data.mid(pos, (toc.at(i+1) & 0xFFFFFF) - pos)));
					if(!textures.last().isValid()) {
						qWarning() << "CharaModel::open tim error: unknown format!" << name << i;
					}
				}

			//	qDebug() << "charaModel ouvert" << _name;

				models.append(CharaModel(name, textures));
//				qDebug() << "Tim ajouté" << name;
			} else {
				qWarning() << "CharaFile::open Unknown format (5)!" << i << QString::number(timOffset, 16);
				return false;
			}
		}
	}

	return true;
}

const CharaModel &CharaFile::model(int id) const
{
	return models.at(id);
}

void CharaFile::setModel(int id, const CharaModel &model)
{
	models.replace(id, model);
	modified = true;
}

int CharaFile::modelCount() const
{
	return models.size();
}
