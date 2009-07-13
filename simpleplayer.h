// simple phonon media player
// GPL 2 or later
// copyright 2009 sandsmark
// love long and prosper

#ifndef SIMPLEPLAYER_H
#define SIMPLEPLAYER_H

#include <iostream>
#include <QLabel>
#include <QVector>

#include <phonon/audiodataoutput.h>

#include "fht.h"

class SimpleOutput : public QWidget
{
  Q_OBJECT

public:
    SimpleOutput() : QWidget(0), m_fht(9), m_pixmap(512, 200) {
        QVector<float> foo(512, 0);
        m_history=foo.toStdVector();
        show();
    }

public slots:
    void handle(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &);
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*) { m_pixmap = QPixmap(size()); m_pixmap.fill(Qt::transparent); }


private:
    FHT m_fht;
    QPixmap m_pixmap;
    std::vector<float> m_history;
};

#endif

