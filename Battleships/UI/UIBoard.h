#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <vector>
#include "SPosition.h"
#include "UIConstants.h"
class UIBoard : public QGraphicsView {
    Q_OBJECT


public:
    UIBoard(QWidget* parent = nullptr);
    virtual ~UIBoard();

    virtual void initializeBoard(std::array<std::list<Position>, 5> cats);

    virtual void drawBackground(QPainter* painter, const QRectF& rect) override;

    void setCellVisible(int row, int col, bool visible);

    void setCatPlacedSuccessfully(bool value);

    bool getCatPlacedSuccessfully();

protected:
    QGraphicsScene* m_scene;
    QImage m_backGroundImage;
    QImage m_cellImage;
    QPixmap m_hitPixmap;
	QPixmap m_missPixmap;
                  
    bool m_gridVisible;
    std::vector<std::vector<QGraphicsPixmapItem*>> m_cells;
    bool m_catPlacedSuccessfully = false;
};

#endif 
