#ifndef DEFINITIONS_H
#define DEFINITIONS_H

enum constructionDirection{
    horizontal,
    vertical
  };
enum constructionStartIndexType{
    tileStartIndex,
    lineStartIndex,
    columnStartIndex
};

//WeightMap is dynamically created when creating Handler object with following parameters
struct constructParameters{
        constructParameters() = delete;
        constructParameters( const constructionStartIndexType _startIndexType,
                                      const int& _startIndex,
                                      const int& _applyLength,
                                      const int& _tileOrWeightmapIndex,
                                      const bool _jumpLinesColumns,
                                      const int& _applyToHowManyConsecutiveLinesColumns,
                                      const constructionDirection _direction){

            startIndex = _startIndex;
            indexType = _startIndexType ;
            tileOrWeightMapIndex = _tileOrWeightmapIndex;
            applyLength = _applyLength;
            jumpLinesColumns = _jumpLinesColumns;
            applyToHowManyConsecutiveLinesColumns = _applyToHowManyConsecutiveLinesColumns;
            direction = _direction;
        }


   //On what index to start applying weightmap/precollapsed.
   int startIndex;
   //Does the index refer to a Tile, a line number or a column number?
   constructionStartIndexType indexType;
   //apply to how many tiles? -1 --> Till end of line (or till end if jumpLineColum is true)
   //If applyLength is != -1 then jumpLines is ignored
   int applyLength;
   //Depending on context this index specifies a tile no. or a WeightMap
   int tileOrWeightMapIndex;
   //Apply only to current line/column or break to next line
   bool jumpLinesColumns;
   //Index of available disadvantage WeightList/precollapsed
   //Apply same thing to how many Lines/Columns?
   int applyToHowManyConsecutiveLinesColumns;
   //In what direction to apply the weights/precollapsed?
   //Specifying when StartIndexType is Line or Column is invalid
   constructionDirection direction;


};


#endif // DEFINITIONS_H
