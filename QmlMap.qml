//import QtQuick 2.0
//import QtLocation 5.9
//import QtPositioning 5.0

//Item {
//    id: window
//    property double latitude: 33.5039800
//    property double longitude: 11.1121500
//    property Component locationmarker: locmarker
//    Plugin {
//        id: googlemapview
//        name: "osm" // Vérifiez si le plugin "osm" est correct pour votre utilisation
//    }
//    Map {
//        id: mapview
//        anchors.fill: parent
//        plugin: googlemapview
//        center: QtPositioning.coordinate(latitude, longitude)
//        zoomLevel: 5
//    }
//    function setCenterPosition(lati, longi) {
//        mapview.center = QtPositioning.coordinate(lati, longi);
//        latitude = lati;
//        longitude = longi;
//    }
//    function setLocationMarking(lati, longi) {
//        var item = locationmarker.createObject(window, {
//            coordinate: QtPositioning.coordinate(lati, longi)
//        });
//        mapview.addMapItem(item);
//    }

//    Component {
//        id: locmarker
//        MapQuickItem {
//            id: markerImg
//            anchorPoint.x: image.width / 4
//            anchorPoint.y: image.height
//            coordinate: position
//            sourceItem: Image {
//                id: image
//                width: 20
//                height: 20
//                source: "https://www.pngarts.com/files/3/Map-Marker-Pin-PNG-Image-Background.png" // Assurez-vous que le chemin est correct
//            }
//        }
//    }
//// Vous pouvez appeler directement les fonctions ici
//    Component.onCompleted: {
//        setCenterPosition(33.5039800, 11.1121500);
//        setLocationMarking(33.5039800, 11.1121500);
//    }
//}
import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.0

Item {
    id: window
    property double latitude: 33.5039800
    property double longitude: 11.1121500
    property Component locationmarker: locmarker
    Plugin {
        id: googlemapview
        name: "osm" // Check if the "osm" plugin is correct for your use
    }
    Map {
        id: mapview
        anchors.fill: parent
        plugin: googlemapview
        center: QtPositioning.coordinate(latitude, longitude)
        zoomLevel: 20
    }
    function setCenterPosition(lati, longi) {
        mapview.center = QtPositioning.coordinate(lati, longi);
        latitude = lati;
        longitude = longi;
    }
    function setLocationMarking(lati, longi) {
        var item = locationmarker.createObject(window, {
            coordinate: QtPositioning.coordinate(lati, longi)
        });
        mapview.addMapItem(item);
    }

    Component {
        id: locmarker
        MapQuickItem {
            id: markerImg
            coordinate: position
            anchorPoint.x: image.width / 2
            anchorPoint.y: image.height // This might need adjustment based on the size and shape of your marker image
            sourceItem: Image {
                id: image
                width: 50 // Adjust according to your marker image size
                height: 50 // Adjust according to your marker image size
                source: "qrc:/new/prefix1/Map-Marker-Pin-PNG-Image-Background.png" // Ensure the URL is correct and accessible
            }
        }
    }

    Component.onCompleted: {
        setCenterPosition(33.5039800, 11.1121500);
        setLocationMarking(33.5039800, 11.1121500);
    }
}
