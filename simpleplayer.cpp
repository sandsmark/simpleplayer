// simple phonon media player
// GPL 2 or later
// copyright 2009 sandsmark
// love long and prosper

#include <iostream>

#include <QObject>
#include <QCoreApplication>
#include <QUrl>

#include <phonon/phononnamespace.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/audiodataoutput.h>

class Output : public QObject
{
  Q_OBJECT

public:
    void handle(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &data) {
        foreach (qint16 i, data.value(Phonon::AudioDataOutput::LeftChannel))
            std::cout << i;
    }
};

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

    Output dumper;
    dumper.connect(&dataout, SIGNAL(dataReady(const QMap<Phonon::AudioDataOutput::Channel, QVector<float> > &data)),
                   &dumper, SLOT(handle(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >)));

    media.setCurrentSource(url);
    media.play();

    app.exec();
}

#include <moc_simpleplayer.cxx>
