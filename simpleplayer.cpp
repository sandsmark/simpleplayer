// simple phonon media player
// GPL 2 or later
// copyright 2009 sandsmark
// love long and prosper

#include <iostream>

#include <QApplication>
#include <QUrl>

#include <phonon/phononnamespace.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/audiodataoutput.h>

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

    QApplication app(argc, argv);
    app.setApplicationName("simpleplayer");

    Phonon::AudioOutput output(Phonon::MusicCategory, &app);
    Phonon::MediaObject media(&app);
    media.connect(&media, SIGNAL(finished()), &app, SLOT(quit()));

    std::cout << " -------------- CREATING AudioDataOutput -------------- " << std::endl;
    Phonon::AudioDataOutput dataout(&app);
    std::cout << " ------------- CONNECTING AudioDataOutput ------------- " << std::endl;
    Phonon::createPath(&media, &dataout);
    Phonon::createPath(&dataout, &output);
    std::cout << " ------------------------ DONE ------------------------ " << std::endl;


    media.setCurrentSource(url);
    media.play();

    app.exec();
}

