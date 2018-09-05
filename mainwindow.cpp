#include <QtGui>
#include "mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set the window properties.
    setWindowTitle(tr("Hexagon Draw Test"));
    resize(768, 768);
}

CMainWindow::~CMainWindow()
{
    // Intentionally left blank.
}

void CMainWindow::paintEvent(QPaintEvent *apEvent)
{
    if (nullptr != apEvent)
    {
        // Draw the hexagon at 512x512 with a size of 256 pixels.
        QPointF qCenter(width() / 2.0, height() / 2.0);
        const float nHexSz = 256.0f;

        QPainter *pPainter = new QPainter();
        pPainter->begin(this);
        DrawHexagon(pPainter, qCenter, nHexSz);
        pPainter->end();

        if (nullptr != pPainter) { delete pPainter; }
    }
    else
    {
        qCritical("apEvent for paintEvent is a nullptr! Aborting paint!");
    }
}

/*!
 * \brief CMainWindow::DrawHexagon
 *
 * This function is used to draw a simple hexagon (using algrebra) as quickly as possibly. The method will use the provided QPainter to render to the widget.
 * This method only calculates the verticies and places them.
 *
 * \param[in] pPainter - Pointer to a valid QPainter object for the canvas widget.
 * \return True if successfull, False otherwise.
 */
bool CMainWindow::DrawHexagon(QPainter *pPainter, const QPointF aCenter, const float aSize)
{
    bool bSuccess = false;

    if (nullptr != pPainter)
    {
        if (!aCenter.isNull() && aSize > 0.0f)
        {
            /*
             * These values are used in calculations. They're approximates, so accuracy isn't going to happen.
             * These are based off of "docs/hexagon_dissection.png".
             * These Are defined as
                    * "long-leg" : "short-leg" (1:2)
                    * "long-leg" : "short-start" (1:4)
                    * "half-width" = 0.86 : "short-leg" (0.86:1)
             * Static_cast is more than likely unecessary, we're just doing it to ensure we have floats.
             */
            const float c_nLongShortRatio = static_cast<float>(1.0f / 2.0f);
            const float c_nShortStartRatio = static_cast<float>(1.0f / 4.0f);
            const float c_nHalfWidthRatio = static_cast<float>(0.86f / 1.0f);

            // Simple variable to help us track half-height of the polygon.
            const float c_nHalfHeight = aSize / 2.0f;

            // Instantiate a new set of verticies.
            const size_t c_iNumVerts = 6;
            QPointF pPts[c_iNumVerts];
            memset(pPts, 0, sizeof(QPointF) * c_iNumVerts);

            // Begin calculating the points (clockwise, starting at top).
            //!\NOTE: Our hexagons have the long-leg vertical, meaning they're pointed at the top. (height > width)
            float nX = aCenter.x();
            float nY = aCenter.y() - c_nHalfHeight;
            pPts[0].setX(nX);
            pPts[0].setY(nY);

            // Top-right vertex.
            nX += (aSize * c_nLongShortRatio) * c_nHalfWidthRatio;
            nY += (aSize * c_nShortStartRatio);
            pPts[1].setX(nX);
            pPts[1].setY(nY);

            // Bottom-right vertex.
            nY += (aSize * c_nLongShortRatio);
            pPts[2].setX(nX);
            pPts[2].setY(nY);

            // Bottom vertex.
            nX -= (aSize * c_nLongShortRatio) * c_nHalfWidthRatio;
            nY += (aSize * c_nShortStartRatio);
            pPts[3].setX(nX);
            pPts[3].setY(nY);

            // Bottom-left vertex.
            nX -= (aSize * c_nLongShortRatio) * c_nHalfWidthRatio;
            nY -= (aSize * c_nShortStartRatio);
            pPts[4].setX(nX);
            pPts[4].setY(nY);

            // Top-left vertex.
            nY -= (aSize * c_nLongShortRatio);
            pPts[5].setX(nX);
            pPts[5].setY(nY);

            // Done, now we want to set the painter to draw the hexagon correctly.
            pPainter->setPen(QPen(QBrush(Qt::black), 2.0f));

            // Draw the points!
            pPainter->drawPolygon(pPts, c_iNumVerts);

            // Set success!
            bSuccess = true;
        }
        else
        {
            qFatal("ASSERT ERROR: Hexagon geometry is invalid!");
        }
    }
    else
    {
        qFatal("ASSERT ERROR: pPainter is NULL! Please try again!");
    }

    return bSuccess;
}
