// simple phonon media player
// GPL 2 or later
// copyright 2009 sandsmark
// love long and prosper

#ifndef SIMPLEPLAYER_H
#define SIMPLEPLAYER_H

#include <iostream>

#include <phonon/audiodataoutput.h>

class SimpleOutput : public QObject
{
  Q_OBJECT

public slots:
    void handle(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &data) {
        foreach (qint16 i, data.value(Phonon::AudioDataOutput::LeftChannel))
            std::cout << (char)i;
    }
};

#endif

