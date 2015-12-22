
#include "header/ClassObject.h"

ClassObject::ClassObject(){
}

ClassObject::ClassObject(QPoint size, QColor colour){

    this->size = size;
    this->colour = colour;
    name = "class name";
    attributes.push_back("attribute 1");
    attributes.push_back("attribute 2");
    attributes.push_back("attribute 3");
    methods.push_back("method 1");
    methods.push_back("method 2");
    methods.push_back("method 3");
    nameFont = QFont("Sans", 10, QFont::Bold);
    textFont = QFont("Sans", 10);
    paddingCoefficient = 0.2;
    updateDrawingParameters();
}

ClassObject::~ClassObject(){
}

void ClassObject::setSize(QPoint size){

    if(size.y() < bottomLineY) this->size.setY(bottomLineY);
    Element::setSize(this->size);
}

void ClassObject::updateDrawingParameters(){

    namePadding = QFontMetrics(nameFont).height() * paddingCoefficient;
    textPadding = QFontMetrics(textFont).height() * paddingCoefficient;
    separatorLine1Y = QFontMetrics(nameFont).height() + 2 * namePadding;
    separatorLine2Y = separatorLine1Y + (QFontMetrics(textFont).height() + 2 * textPadding) * attributes.length();
    bottomLineY = separatorLine2Y + (QFontMetrics(textFont).height() + 2 * textPadding) * methods.length();
    setSize(size);
}

void ClassObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(colour);
    painter->drawRect(0, 0, size.x(), size.y());
    painter->drawLine(0, separatorLine1Y, size.x(), separatorLine1Y);
    painter->drawLine(0, separatorLine2Y, size.x(), separatorLine2Y);

    painter->setFont(nameFont);
    painter->drawText((size.x() - painter->fontMetrics().width(name)) * 0.5,
                      QFontMetrics(nameFont).ascent() + namePadding,
                      name);

    painter->setFont(textFont);
    for(int i = 0; i < attributes.length(); i++){
        painter->drawText(textPadding,
                          separatorLine1Y + (i + 1) * (QFontMetrics(textFont).ascent() + textPadding) + i * (QFontMetrics(textFont).descent() + textPadding),
                          attributes.at(i));
    }

    for(int i = 0; i < methods.length(); i++){
        painter->drawText(textPadding,
                          separatorLine2Y + (i + 1) * (QFontMetrics(textFont).ascent() + textPadding) + i * (QFontMetrics(textFont).descent() + textPadding),
                          methods.at(i));
    }
}
