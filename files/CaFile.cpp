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
#include "files/CaFile.h"

CaFile::CaFile()
	: File()
{
}

bool CaFile::open(const QByteArray &ca)
{
	const char *ca_data = ca.constData();
	int ca_data_size = ca.size();
	quint32 i;

	cameras.clear();

	if(ca_data_size != 38 && ca_data_size % 40 != 0) {
		qWarning() << "size ca error" << ca_data_size << sizeof(Camera);
		return false;
	}

	if(sizeof(Camera) != 40) {
		qWarning() << "sizeof ca struct error" << sizeof(Camera);
		return false;
	}

	Camera camera;

	quint32 caCount = (ca_data_size / 40) + int(ca_data_size % 40 >= 38);

	for(i=0 ; i<caCount ; ++i) {
		memcpy(&camera, &ca_data[i*40], 38);

		cameras.append(camera);
	}

	modified = false;

	return true;
}

bool CaFile::save(QByteArray &ca)
{
	foreach(Camera camera, cameras) {
		camera.camera_axis2z = camera.camera_axis[2].z;
		camera.camera_zoom2 = camera.camera_zoom;
		ca.append((char *)&camera, sizeof(Camera));
	}

	return true;
}

bool CaFile::hasCamera() const
{
	return !cameras.isEmpty();
}

int CaFile::cameraCount() const
{
	return cameras.size();
}

const Camera &CaFile::camera(int camID) const
{
	return cameras.at(camID);
}

void CaFile::setCamera(int camID, const Camera &cam)
{
	cameras[camID] = cam;
	modified = true;
}

void CaFile::insertCamera(int camID, const Camera &cam)
{
	cameras.insert(camID, cam);
	modified = true;
}

void CaFile::removeCamera(int camID)
{
	if(cameras.size() > 1) {
		cameras.removeAt(camID);
		modified = true;
	}
}
