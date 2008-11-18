/*
 * mpristunecontroller.h
 * Copyright (C) 2008 Matthieu Volat
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

#ifndef MPRISCONTROLLER_H
#define MPRISCONTROLLER_H

#include <QDBusConnection>
#include <QString>

#include "tunecontrollerinterface.h"
#include "tune.h"

struct PlayerStatus
{
	int i1;
	int i2;
	int i3;
	int i4;
};

Q_DECLARE_METATYPE(PlayerStatus)

class MPRISController : public TuneController
{
	Q_OBJECT

public:
	MPRISController();

	Tune currentTune();

protected slots:
	void playerStatusChanged(const PlayerStatus& ps);
	void playerTrackChanged(QVariantMap map);

private:
	Tune currentTune_;
};

#endif
