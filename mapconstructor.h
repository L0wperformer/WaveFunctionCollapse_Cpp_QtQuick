#ifndef MAPCONSTRUCTOR_H
#define MAPCONSTRUCTOR_H

#include <QObject>

class MapConstructor : public QObject
{
    Q_OBJECT
public:
    enum constructionDirection{
        horizontal,
        vertical
    };
    enum constructionStartIndexType{
        tileStartIndex,
        lineStartIndex,
        columnStartIndex
    };

    struct constructParameters{
        constructParameters() = delete;
        constructParameters( const constructionStartIndexType _startIndexType,
                            const int& _startIndex,
                            const int& _applyLength,
                            const int& _tileOrWeightmapIndex,
                            const bool _jumpLinesColumns,
                            const int& _applyToHowManyConsecutiveLinesColumns,
                            const constructionDirection _direction,
                            const bool _relative = true,
                            const bool _applyHighlight = false){

            startIndex = _startIndex;
            indexType = _startIndexType ;
            tileOrWeightMapIndex = _tileOrWeightmapIndex;
            applyLength = _applyLength;
            jumpLinesColumns = _jumpLinesColumns;
            applyToHowManyConsecutiveLinesColumns = _applyToHowManyConsecutiveLinesColumns;
            direction = _direction;
            applyHighlight = _applyHighlight;
            relative = _relative;
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
        //Apply Highlight to tiles affected by this
        bool applyHighlight;
        //Are the values absolute or relative to the Total resolution
        bool relative;

    };

public:
    MapConstructor(const QList<constructParameters>& params, const int& dimensionsWidth,const int& dimensionsHeight );
    QList<int> constructWeightmap();
    QList<int> getTilesAffectedByMap();

private:
    QList<constructParameters> m_params;
    QList<int> m_weightMap;
    int m_dimensionsWidthHeight;
    int m_dimensionsWidth;
    int m_dimensionsHeight;


};

#endif // MAPCONSTRUCTOR_H
