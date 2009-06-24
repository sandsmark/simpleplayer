// simple phonon media player
// GPL 2 or later
// copyright 2009 sandsmark
// love long and prosper

#include "simpleplayer.h"

#include <iostream>

#include <QCoreApplication>
#include <QUrl>

#include <phonon/audiodataoutput.h>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/phononnamespace.h>

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " URL" << std::endl;
        return 0;
    }

    QUrl url(argv[1], QUrl::TolerantMode);

    if (!url.isValid())
    {
        std::cout << "Please supply a valid URL!" << std::endl;
        return 0;
    }

    QCoreApplication app(argc, argv);
    app.setApplicationName("simpleplayer");

    Phonon::AudioOutput output(Phonon::MusicCategory, &app);
    Phonon::MediaObject media(&app);
    media.connect(&media, SIGNAL(finished()), &app, SLOT(quit()));

    Phonon::AudioDataOutput dataout(&app);
    Phonon::createPath(&media, &dataout);
    Phonon::createPath(&dataout, &output);

    SimpleOutput dumper;
    dumper.connect(&dataout, SIGNAL(dataReady(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)),
                   &dumper,  SLOT(handle(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)),
		   Qt::DirectConnection);

    media.setCurrentSource(url);
    media.play();

    app.exec();
}

