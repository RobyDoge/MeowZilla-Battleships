#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <vector>

struct UIPosition {
    int row;
    int col;
};

class UIBoard : public QGraphicsView {
    Q_OBJECT

protected:
    QGraphicsScene* scene;
    QImage backGroundImage;   
    QImage cellPixmap;        
    QPixmap hitPixmap;
	QPixmap missPixmap;
    
    int cellSize = 70;               
    bool gridVisible;         
    std::vector<std::vector<QGraphicsPixmapItem*>> cells; 

public:
    UIBoard(QWidget* parent = nullptr);
    virtual ~UIBoard();

    // Inițializează tabla
    virtual void initializeBoard(std::array<std::list<UIPosition>, 5> catPositions);

    // Desenează fundalul
    virtual void drawBackground(QPainter* painter, const QRectF& rect) override;

    // Afișează un anumit asset într-o celulă
    void updateCell(int row, int col, const QPixmap& pixmap);

    // Setează vizibilitatea unui grid
    void setGridVisibility(bool visible);

    // Setează vizibilitatea unei celule individuale
    void setCellVisible(int row, int col, bool visible);
};

#endif // BOARD_H
