/*
 * psifileplugin.cpp
 * Copyright (C) 2006  Remko Troncon
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#define QT_STATICPLUGIN

#include <QtCore>
#include <QObject>
#include <QString>

#include "tunecontrollerplugin.h"
#include "psifilecontroller.h"


/**
 * \brief A TuneController plugin for the Psi file controller.
 */
class PsiFilePlugin : public QObject, public TuneControllerPlugin
{
	Q_OBJECT
	Q_INTERFACES(TuneControllerPlugin)

public:
	virtual QString name();
	virtual TuneController* createController();
};

Q_EXPORT_PLUGIN2(psifileplugin, PsiFilePlugin);

QString PsiFilePlugin::name()
{
	return "Psi File";
}

TuneController* PsiFilePlugin::createController() 
{
	return new PsiFileController();
}

#include "psifileplugin.moc"