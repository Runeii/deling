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
#ifndef WALKMESHWIDGET_H
#define WALKMESHWIDGET_H

#include <QtGui>
#include "widgets/PageWidget.h"
#include "WalkmeshGLWidget.h"
#include "VertexWidget.h"
#include "OrientationWidget.h"

class WalkmeshWidget : public PageWidget
{
	Q_OBJECT
public:
	WalkmeshWidget(QWidget *parent=0);
	void clear();
	void fill();
	inline QString tabName() const { return tr("Walkmesh"); }
	int currentCamera() const;
public slots:
	void setCurrentCamera(int camID);
private slots:
	void editCaVector(const Vertex_s &values);
	void editCaPos(double value);
	void editCaZoom(int value);
	void setCurrentId(int i);
	void editIdTriangle(const Vertex_s &values);
	void editIdAccess(int value);
    void setCurrentGateway(int id);
	void setCurrentDoor(int id);
	void editExitPoint(const Vertex_s &values);
	void editEntryPoint(const Vertex_s &values);
	void editDoorPoint(const Vertex_s &values);
	void editFieldId(int v);
	void editDoorId(int v);
	void setCurrentRange1(int id);
	void setCurrentRange2(int id);
	void editRange(int v);
	void editUnknownGate(int val);
	void editUnknownGate(const QString &u);
    void setCurrentMoviePosition(int id);
	void setMovieCameraPageEnabled(bool enabled);
	void addMovieCameraPosition();
	void removeMovieCameraPosition();
	void editNavigation(int v);
	void editUnknown(const QString &u);
private:
	void build();
	QWidget *buildCameraPage();
	QWidget *buildWalkmeshPage();
	QWidget *buildGatewaysPage();
	QWidget *buildDoorsPage();
	QWidget *buildCameraRangePage();
	QWidget *buildMovieCameraPage();
	QWidget *buildMiscPage();
	void editCaVector(int id, const Vertex_s &values);
	void editCaPos(int id, double value);
	void editIdTriangle(int id, const Vertex_s &values);
	void editIdAccess(int id, int value);
	void editExitPoint(int id, const Vertex_s &values);
	void editDoorPoint(int id, const Vertex_s &values);
	void editRange1(int id, int v);
	void editRange2(int id, int v);
	void editUnknownGate(int id, int val);

	WalkmeshGLWidget *walkmeshGL;
	QTabWidget *tabWidget;
	//CamPage
	QComboBox *camSelect;
	VertexWidget *caVectorXEdit, *caVectorYEdit, *caVectorZEdit;
	QDoubleSpinBox *caSpaceXEdit, *caSpaceYEdit, *caSpaceZEdit;
	QSpinBox *caZoomEdit;
	//WalkmeshPage
	QListWidget *idList;
	VertexWidget *idVertices[3];
	QSpinBox *idAccess[3];
	//GatePage
	QListWidget *gateList;
	QLineEdit *unknownGate2;
	QSpinBox *unknownGate1[4], *fieldId;
	VertexWidget *exitPoints[2], *entryPoint;
	//DoorPage
	QListWidget *doorList;
	QSpinBox *doorId;
	VertexWidget *doorPosition[2];
	//CameraRangePage
	QListWidget *rangeList1, *rangeList2;
	QSpinBox *rangeEdit1[4], *rangeEdit2[4];
	//MovieCamPage
	QListWidget *frameList;
	QToolBar *camToolbar;
	QAction *camPlusAction, *camMinusAction;
    VertexWidget *camPoints[4];
	//MiscPage
	OrientationWidget *navigation;
	QSpinBox *navigation2;
	QLineEdit *unknown;
protected:
	void focusInEvent(QFocusEvent *);
};

#endif // WALKMESHWIDGET_H
