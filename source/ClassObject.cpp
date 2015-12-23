
#include "header/ClassObject.h"
#include "qteditorfactory.h"

ClassObject::ClassObject(){
}

ClassObject::ClassObject(QPoint size, QColor colour){

    groupPropertyManager = new QtGroupPropertyManager(this);
    stringPropertyManager = new QtStringPropertyManager(this);
    name = stringPropertyManager->addProperty("Name");
    classGroup = groupPropertyManager->addProperty("Class");

    classGroup->addSubProperty(name);
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
    stringPropertyManager->setValue(name, "class name");

    attributes.push_back("attribute 1");
    attributes.push_back("attribute 2");
    attributes.push_back("attribute 3");
    methods.push_back("method 1");
    methods.push_back("method 2");
    methods.push_back("method 3");
    nameFont = QFont("Sans", 10, QFont::Bold);
    textFont = QFont("Sans", 10);
    paddingCoefficient = 0.2;

    connect(pointPropertyManager, SIGNAL(valueChanged(QtProperty*,QPoint)), this, SLOT(pointPropertyUpdated(QtProperty*,QPoint)));
    connect(stringPropertyManager, SIGNAL(valueChanged(QtProperty*,QString)), this, SLOT(stringPropertyUpdated(QtProperty*,QString)));
    connect(colorPropertyManager, SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(update()));

    updateDrawingParameters();
    setSize(size);
}

ClassObject::~ClassObject(){
}

void ClassObject::pointPropertyUpdated(QtProperty* property, QPoint size){
    if (property == sizep){
        updateDrawingParameters();
        setSize(size);
    }
    else if (property == this->size && (pointPropertyManager->value(this->size).x() != pointPropertyManager->value(sizep).x() ||
                                  pointPropertyManager->value(this->size).y() != pointPropertyManager->value(sizep).y())){
        pointPropertyManager->blockSignals(true);
        pointPropertyManager->setValue(sizep, size);

        pointPropertyManager->blockSignals(false);
    }
}

void ClassObject::stringPropertyUpdated(QtProperty* property, QString string){
    Q_UNUSED(property)
    Q_UNUSED(string)
    updateDrawingParameters();
    setSize(pointPropertyManager->value(this->size));
    update();
}

void ClassObject::setSize(QPoint size){

    //enforce minimum size of the element so that all text fits inside it
    if(size.y() < bottomLineY) size.setY(bottomLineY);
    if(size.x() < edgeLineX) size.setX(edgeLineX);
    Element::setSize(size);
}

void ClassObject::updateDrawingParameters(){

    namePadding = QFontMetrics(nameFont).height() * paddingCoefficient;
    textPadding = QFontMetrics(textFont).height() * paddingCoefficient;

    separatorLine1Y = QFontMetrics(nameFont).height() + 2 * namePadding;
    separatorLine2Y = separatorLine1Y + (QFontMetrics(textFont).height() + 2 * textPadding) * attributes.length();

    bottomLineY = separatorLine2Y + (QFontMetrics(textFont).height() + 2 * textPadding) * methods.length();

    edgeLineX = pointPropertyManager->value(sizep).x();
    int compareWidth = QFontMetrics(nameFont).width(stringPropertyManager->value(name)) + 2 * namePadding;
    if(compareWidth > edgeLineX) edgeLineX = compareWidth;

    for(int i = 0; i < attributes.length(); i++){
        compareWidth = QFontMetrics(textFont).width(attributes.at(i)) + 2 * textPadding;
        if(compareWidth > edgeLineX) edgeLineX = compareWidth;
    }

    for(int i = 0; i < methods.length(); i++){
        compareWidth = QFontMetrics(textFont).width(methods.at(i)) + 2 * textPadding;
        if(compareWidth > edgeLineX) edgeLineX = compareWidth;
    }

}

void ClassObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(colorPropertyManager->value(colourp));
    painter->drawRect(0, 0, pointPropertyManager->value(size).x(), pointPropertyManager->value(size).y());
    painter->drawLine(0, separatorLine1Y, pointPropertyManager->value(size).x(), separatorLine1Y);
    painter->drawLine(0, separatorLine2Y, pointPropertyManager->value(size).x(), separatorLine2Y);

    painter->setFont(nameFont);
    painter->drawText((pointPropertyManager->value(size).x() - painter->fontMetrics().width(stringPropertyManager->value(name))) * 0.5,
                      QFontMetrics(nameFont).ascent() + namePadding,
                      stringPropertyManager->value(name));

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
