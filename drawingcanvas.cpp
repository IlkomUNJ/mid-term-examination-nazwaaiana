#include "drawingcanvas.h"
#include <string>
#include <set>

using namespace std;

std::string matrixToString(bool m[3][3]) {
    std::string s = "";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            s += (m[i][j] ? '1' : '0');
        }
    }
    return s;
}

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    setStyleSheet("background-color: white; border: 1px solid gray;");
}
void DrawingCanvas::clearPoints(){
    m_points.clear();
    update();
}
void DrawingCanvas::paintLines(){
    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::initializeValidPatterns() {
    m_validSegmentPatterns.clear();

    m_validSegmentPatterns.insert("000111000");
    m_validSegmentPatterns.insert("010010010");
    m_validSegmentPatterns.insert("001010100");
    m_validSegmentPatterns.insert("100010001");

    m_validSegmentPatterns.insert("010110000");
    m_validSegmentPatterns.insert("000110010");

    m_validSegmentPatterns.insert("000011000");
}

void DrawingCanvas::segmentDetection(int windowSize) {
    initializeValidPatterns();
    m_segmentCandidates.clear();

    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "Memulai Deteksi Kandidat Segmen Otomatis..." << endl;

    const double SEGMENT_THRESHOLD = 0.20;

    for(int i = 1; i < image.width()-1;i++){
        for(int j = 1; j < image.height()-1;j++){
            bool local_window[3][3] = {false};
            int foregroundPixels = 0;

            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    QRgb rgbValue = image.pixel(i+m, j+n);
                    bool isForeground = (rgbValue != 0xffffffff);
                    local_window[m+1][n+1] = isForeground;
                    if (isForeground) foregroundPixels++;
                }
            }

            bool isSegmentCandidate = false;

            if (local_window[1][1]) {

                std::string pattern = matrixToString(local_window);
                if (m_validSegmentPatterns.count(pattern)) {
                    isSegmentCandidate = true;
                } else {
                    double density = (double)foregroundPixels / 9.0;
                    if (density >= SEGMENT_THRESHOLD) {
                        isSegmentCandidate = true;
                    }
                }
            }

            if (isSegmentCandidate) {
                m_segmentCandidates.append(QPoint(i, j));
            }

        }
    }
    cout << "Deteksi Selesai. Total Kandidat Segmen Ditemukan: " << m_segmentCandidates.size() << endl;
    update();

    return;
}
void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            painter.drawLine(m_points[i], m_points[i+1]);
        }

        isPaintLinesClicked = false;

        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
    update();
}
