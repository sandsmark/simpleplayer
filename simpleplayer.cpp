// simple phonon media player
// GPL 2 or later
// copyright 2009 sandsmark
// love long and prosper

#include "simpleplayer.h"
#include "blockanalyzer.h"

#include <iostream>

#include <QApplication>
#include <QUrl>
#include <QPainter>

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

    QApplication app(argc, argv);
    app.setApplicationName("simpleplayer");

    Phonon::AudioOutput output(Phonon::MusicCategory, &app);
    Phonon::MediaObject media(&app);
    media.connect(&media, SIGNAL(finished()), &app, SLOT(quit()));

    Phonon::AudioDataOutput dataout(&app);
    Phonon::createPath(&media, &dataout);
    Phonon::createPath(&media, &output);
    //Phonon::createPath(&dataout, &output);

    //SimpleOutput dumper;
    BlockAnalyzer dumper(0);
    dumper.connect(&dataout, SIGNAL(dataReady(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)),
                   &dumper,  SLOT(drawFrame(const QMap<Phonon::AudioDataOutput::Channel,      QVector<qint16> >&)));

    dumper.show();

    media.setCurrentSource(QString(argv[1]));
    media.play();

    app.exec();
}

void SimpleOutput::handle(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &data)
{
    float *buffer = new float[512];
    float *input = new float[512];

    for (int i=0; i<512; i++) {
        input[i] = static_cast<float>(data[Phonon::AudioDataOutput::LeftChannel][i]) / static_cast<float>(0x7fff);
    }


    m_fht.copy(buffer, input);
    m_fht.logSpectrum(input, buffer);
    m_fht.scale(buffer, 1.0/20);

    m_fht.ewma(&m_history.front(), buffer, .75);

    m_pixmap.fill(Qt::transparent);
    QPainter paint(&m_pixmap);
    int w = m_pixmap.width()/256;
    for (int i=0; i<256; i++) {
        paint.fillRect(i*w, m_pixmap.height() - m_history[i]*200, w, m_history[i]*200, Qt::black);
    }

    update();
}

void SimpleOutput::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
}
