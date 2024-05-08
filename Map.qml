import QtQuick 2.0
import QtLocation 5.11
import QtPositioning 5.11

Rectangle
{
    id:window

    property double latitude:51.5072
    property double longitude:50.1276

    property  Component Locationmaker: maker
    Plugin
    {
       id:goolemopview
       name:"osm"

    }
    Map
    {
       id:mapview
       anchors.fill: parent
       plugin: goolemopview
       center: QtPositioning.coordinate(latitude,)
    }

}
