/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * mosiac = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    vector<Point<3>> Tile_pixels;
    Tile_pixels.resize(theTiles.size());
    int i = 0;
    map<Point<3>, int> map_tiles;
    for(auto x :theTiles){
        Tile_pixels[i] = convertToXYZ(x.getAverageColor());
        map_tiles.insert( pair<Point<3>, int>(convertToXYZ(x.getAverageColor()),i));
        i++;
    }
    KDTree<3> *tree = new KDTree<3>(Tile_pixels);

    for(int i = 0; i < theSource.getRows() ; i++){
        for(int j = 0; j < theSource.getColumns(); j++){
            LUVAPixel pixel_color = theSource.getRegionColor(i, j);
            Point<3> the_point = tree->findNearestNeighbor(convertToXYZ(pixel_color));
            int index = map_tiles[the_point];
            mosiac->setTile(i, j, &theTiles[index]);
        }
    }
    delete tree;

    return mosiac;
}
