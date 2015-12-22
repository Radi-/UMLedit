
#include "header/ClassObject.h"
#include "qteditorfactory.h"

ClassObject::ClassObject(){
}

ClassObject::ClassObject(QPoint size, QColor colour, QGraphicsItem* parent) : Object(parent){

    connect(pointPropertyManager, SIGNAL(valueChanged(QtProperty*,QPoint)), this, SLOT(updateDrawingParameters()));
    groupPropertyManager = new QtGroupPropertyManager(0);
    stringPropertyManager = new QtStringPropertyManager(0);
    namep = stringPropertyManager->addProperty("Name");
    classGroup = groupPropertyManager->addProperty("Class");

    classGroup->addSubProperty(namep);
    classGroup->addSubProperty(colourp);
    classGroup->addSubProperty(sizep);

    QtSpinBoxFactory* spinBoxFactory = new QtSpinBoxFactory();
    QtLineEditFactory* lineEditFactory = new QtLineEditFactory();
    QtColorEditorFactory* colorFactory = new QtColorEditorFactory();

    propertyBrowser = new QtTreePropertyBrowser();
    propertyBrowser->setFactoryForManager(stringPropertyManager, lineEditFactory);
    propertyBrowser->setFactoryForManager(colorPropertyManager, colorFactory);
    propertyBrowser->setFactoryForManager(pointPropertyManager->subIntPropertyManager(), spinBoxFactory);

    propertyBrowser->addProperty(classGroup);

    pointPropertyManager->setValue(sizep, size);
    colorPropertyManager->setValue(colourp, colour);
    stringPropertyManager->setValue(namep, "class name");

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

    //enforce minimum size of the element so that all text fits inside it
    if(size.y() < bottomLineY) this->size.setY(bottomLineY);
    if(size.x() < edgeLineX) this->size.setX(edgeLineX);
    Element::setSize(this->size);
}

void ClassObject::updateDrawingParameters(){

    prepareGeometryChange();

    namePadding = QFontMetrics(nameFont).height() * paddingCoefficient;
    textPadding = QFontMetrics(textFont).height() * paddingCoefficient;

    separatorLine1Y = QFontMetrics(nameFont).height() + 2 * namePadding;
    separatorLine2Y = separatorLine1Y + (QFontMetrics(textFont).height() + 2 * textPadding) * attributes.length();

    bottomLineY = separatorLine2Y + (QFontMetrics(textFont).height() + 2 * textPadding) * methods.length();

    edgeLineX = pointPropertyManager->value(sizep).x();
    int compareWidth = QFontMetrics(nameFont).width(name) + 2 * namePadding;
    if(compareWidth > edgeLineX) edgeLineX = compareWidth;

    for(int i = 0; i < attributes.length(); i++){
        compareWidth = QFontMetrics(textFont).width(attributes.at(i)) + 2 * textPadding;
        if(compareWidth > edgeLineX) edgeLineX = compareWidth;
    }

    for(int i = 0; i < methods.length(); i++){
        compareWidth = QFontMetrics(textFont).width(methods.at(i)) + 2 * textPadding;
        if(compareWidth > edgeLineX) edgeLineX = compareWidth;
    }

    //setSize(size);
}

void ClassObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(colorPropertyManager->value(colourp));
    painter->drawRect(0, 0, pointPropertyManager->value(sizep).x(), pointPropertyManager->value(sizep).y());
    painter->drawLine(0, separatorLine1Y, pointPropertyManager->value(sizep).x(), separatorLine1Y);
    painter->drawLine(0, separatorLine2Y, pointPropertyManager->value(sizep).x(), separatorLine2Y);

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

QtTreePropertyBrowser* ClassObject::getPropertyBrowser(){
    return propertyBrowser;
}
