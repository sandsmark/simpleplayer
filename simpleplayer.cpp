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
    
    Phonon::AudioOutput output(Phonon::MusicCategory, &app);
    Phonon::MediaObject media(&app);
    Phonon::createPath(&media, &output);

    media.setCurrentSource(url);
    media.play();

    app.exec();
}

