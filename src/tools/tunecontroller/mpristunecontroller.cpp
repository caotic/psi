/*
 * mpristunecontroller.cpp 
 * Copyright (C) 2008  Matthieu Volat 
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

#include <QtDBus/QDBusMetaType>
#include <QDBusReply>
#include <QVariantMap>

#include "mpristunecontroller.h"

/**
 * \class MPRISTuneController
 * \brief A common controller class for MPRIS compilant players.
 */

QDBusArgument &operator<<(QDBusArgument& arg, const PlayerStatus& ps)
{
	arg.beginStructure();
	arg << ps.i1;
	arg << ps.i2;
	arg << ps.i3;
	arg << ps.i4;
	arg.endStructure();
	return arg;
}

const QDBusArgument &operator>>(const QDBusArgument& arg, PlayerStatus& ps)
{
	arg.beginStructure();
	arg >> ps.i1;
	arg >> ps.i2;
	arg >> ps.i3;
	arg >> ps.i4;
	arg.endStructure();
	return arg;
}

MPRISTuneController::MPRISTuneController(const QString& player)
{
	service_ = QString("org.mpris.") + player;
	QDBusConnection bus = QDBusConnection::sessionBus();

	qDBusRegisterMetaType<PlayerStatus>();
	bus.connect(
			service_,
			"/Player",
			"org.freedesktop.MediaPlayer",
			"StatusChange",
			"(iiii)",
			this,
			SLOT(playerStatusChanged(PlayerStatus)));

	bus.connect(
			service_,
			"/Player",
			"org.freedesktop.MediaPlayer",
			"TrackChange",
			"a{sv}",
			this,
			SLOT(playerTrackChanged(QVariantMap)));
}

Tune MPRISTuneController::currentTune()
{
	return currentTune_;
}

void MPRISTuneController::playerStatusChanged(const PlayerStatus& ps)
{
	// Many players do not send TrackChange when pausing/stopping, so
	// we must use StatusChange instead of
	if (ps.i1 != 0)
		emit stopped();
}

void MPRISTuneController::playerTrackChanged(QVariantMap map)
{
	currentTune_.setName(map.value("title").toString());
	currentTune_.setArtist(map.value("artist").toString());
	currentTune_.setAlbum(map.value("album").toString());
	currentTune_.setTrack(map.value("track").toString());
	currentTune_.setTime(map.value("time").toUInt());
	emit playing(currentTune_);
}
