#include "MapParser.hpp"
#include "Level.hpp"

#include "Utils.hpp"

using namespace tinyxml2;

MapParser::MapParser() {
    level = nullptr;
}
MapParser::MapParser(std::string FILE, Level* level) {
    this->level = level;
    init(FILE);
}
MapParser::~MapParser() {
    cleanup();
}

void MapParser::init(std::string FILE) {
    XMLDocument doc;
    std::string PF = PATH + FILE;
    doc.LoadFile(PF.c_str());
    PF = PATH + doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("source");
    parseTileset(PF.c_str());

    firstTileID = doc.FirstChildElement("map")->FirstChildElement("tileset")->IntAttribute("firstgid");

    XMLElement* element = doc.FirstChildElement("map");
    parseGroups(element);
}
void MapParser::cleanup() {

}

void MapParser::parseTileset(std::string FILE) {
    XMLDocument doc;
    doc.LoadFile(FILE.c_str());
    XMLElement* e = doc.FirstChildElement("tileset");

    tilesetArray.x = 0;
    tilesetArray.y = 0;
    int S = 0;
    e->QueryIntAttribute("tilecount", &S);
    e->QueryIntAttribute("columns", &tilesetArray.x);

    tilesetArray.y = S / tilesetArray.x;

    int margin = 0;
    int spacing = 0;

    e->QueryIntAttribute("margin", &margin);
    e->QueryIntAttribute("spacing", &spacing);

    int tilewidth = 1;
    int tileheight = 1;
    e->QueryIntAttribute("tilewidth", &tilewidth);
    e->QueryIntAttribute("tileheight", &tileheight);

    tileSize.x = tilewidth;
    tileSize.y = tileheight;

    for (int y = 0; y < tilesetArray.y; y++) {
        for (int x = 0; x < tilesetArray.x; x++) {
            sf::IntRect rect;

            rect.left = margin + (spacing + tilewidth) * x;
            rect.top = margin + (spacing + tileheight) * y;
            rect.width = tilewidth;
            rect.height = tileheight;

            subRects.push_back(rect);
        }
    }

    e = e->FirstChildElement("image");
    std::string PF = PATH + e->Attribute("source");
    level->texture = new sf::Texture;
    level->texture->loadFromFile(PF);
}
void MapParser::parseGroups(XMLElement* root) {
    XMLElement* group = root->FirstChildElement("group");
    while (group) {

        XMLElement* c = group->FirstChildElement();

        if (strcmp(c->Name(), "imagelayer") == 0) {
            //TODO: imagelayerParse
            parseImages(c);
        }
        else if (strcmp(c->Name(), "objectgroup") == 0) {
            //TODO: objectgroupParse
            parseObjects(c);
        }
        else if (strcmp(c->Name(), "layer") == 0) {
            //TODO: layerPrase
            parseTiles(c);
        }

        group = group->NextSiblingElement("group");
    }
}
void MapParser::parseObjects(XMLElement* root) {
    /*
    ...
 <group id="72" name="objects">
  <objectgroup color="#ff0000" id="70" name="objects">
   <object id="21" name="Rectangle" type="rectangle" x="16" y="144" width="176" height="96"/>
   <object id="22" name="Point" type="point" x="224" y="176">
    <point/>
   </object>
   <object id="23" name="Elipse" type="elipse" x="256" y="144" width="48" height="48">
    <ellipse/>
   </object>
   <object id="24" name="Polygon" type="polygon" x="384" y="144">
    <polygon points="0,0 -32,48 32,48"/>
   </object>
   <object id="28" name="Text" type="text" x="432" y="176" width="80" height="17.875">
    <text wrap="1">Hello World</text>
   </object>
   <object id="30" name="Tile" type="tile" gid="468" x="480" y="144" width="16" height="16"/>
   </object>
  </objectgroup>
 </group>
    ...
    */

    XMLElement* g = root->Parent()->ToElement();

    float _opacity = 1.0f;
    float _offsetx = 0.f;
    float _offsety = 0.f;
    float _parallaxx = 1.0f;
    float _parallaxy = 1.0f;

    g->QueryFloatAttribute("opacity", &_opacity);
    g->QueryFloatAttribute("offsetx", &_offsetx);
    g->QueryFloatAttribute("offsety", &_offsety);
    g->QueryFloatAttribute("parallaxx", &_parallaxx);
    g->QueryFloatAttribute("parallaxy", &_parallaxy);

    XMLElement* e = root;
    XMLElement* o = e->FirstChildElement("object");

    while (e) {
        ObjectsLayer layer;

        e->QueryBoolAttribute("visible", &layer.visible);
        e->QueryFloatAttribute("opacity", &layer.opacity);
        e->QueryFloatAttribute("offsetx", &layer.offsetx);
        e->QueryFloatAttribute("offsety", &layer.offsety);
        e->QueryFloatAttribute("parallaxx", &layer.parallaxx);
        e->QueryFloatAttribute("parallaxy", &layer.parallaxy);
        layer.offsetx += _offsetx;
        layer.offsety += _offsety;
        layer.parallaxx *= _parallaxx;
        layer.parallaxy *= _parallaxy;

        while (o) {
            sf::ConvexShape polygon;
            float x = 0.0f;
            float y = 0.0f;
            float width = 0.0f;
            float height = 0.0f;

            o->QueryFloatAttribute("x", &x);
            o->QueryFloatAttribute("y", &y);
            o->QueryFloatAttribute("width", &width);
            o->QueryFloatAttribute("height", &height);

            std::vector<sf::Vector2f> points = parsePoints(o->FirstChildElement()->Attribute("points"));

            polygon.setPointCount(points.size());
            for (int i = 0; i < points.size();i++) {
                polygon.setPoint(i, points[i]);
            }
            polygon.setFillColor(sf::Color(255, 0, 0, 100));
            polygon.setOutlineColor(sf::Color::Red);
            polygon.setOutlineThickness(-1.0f);
            polygon.setPosition(sf::Vector2f(x + layer.offsetx, y + layer.offsety));

            layer.shapes.push_back(polygon);
            o = o->NextSiblingElement("object");
        }
        level->objects.push_back(layer);
        e = e->NextSiblingElement("objectgroup");
    }
}
void MapParser::parseImages(XMLElement* root) {

    /*
    ...
 <group id="5" name="bg" locked="1">
  <imagelayer id="69" name="sky" locked="1" parallaxx="0.5" parallaxy="0.8" repeatx="1">
   <image source="../Textures/sky.png" width="112" height="304"/>
    ...
    */

    XMLElement* g = root->Parent()->ToElement();

    float _opacity = 1.0f;
    float _offsetx = 0.f;
    float _offsety = 0.f;
    float _parallaxx = 1.0f;
    float _parallaxy = 1.0f;
    const char* _tintcolor = "#ffffffff";
    sf::Color _color(255, 255, 255, 255);

    g->QueryFloatAttribute("opacity", &_opacity);
    g->QueryFloatAttribute("offsetx", &_offsetx);
    g->QueryFloatAttribute("offsety", &_offsety);
    g->QueryFloatAttribute("parallaxx", &_parallaxx);
    g->QueryFloatAttribute("parallaxy", &_parallaxy);
    if (g->Attribute("tintcolor")) _tintcolor = g->Attribute("tintcolor");
    _color = hexToColor(_tintcolor);
    _color.a *= _opacity;

    XMLElement* e = root;

    while (e) {

        int width = 0;
        int height = 0;
        float opacity = 1.0f;
        float offsetx = 0.f;
        float offsety = 0.f;
        float parallaxx = 1.0f;
        float parallaxy = 1.0f;
        bool repeatx = false;
        bool repeaty = false;
        const char* tintcolor = "#ffffffff";
        sf::Color color(255, 255, 255, 255);
        e->QueryFloatAttribute("opacity", &opacity);
        e->QueryFloatAttribute("offsetx", &offsetx);
        e->QueryFloatAttribute("offsety", &offsety);
        e->QueryFloatAttribute("parallaxx", &parallaxx);
        e->QueryFloatAttribute("parallaxy", &parallaxy);
        e->QueryBoolAttribute("repeatx", &repeatx);
        e->QueryBoolAttribute("repeaty", &repeaty);
        if (e->Attribute("tintcolor")) tintcolor = e->Attribute("tintcolor");
        color = hexToColor(tintcolor);

        XMLElement* _e = e->FirstChildElement();
        std::string PF = PATH + _e->Attribute("source");
        _e->QueryIntAttribute("width", &width);
        _e->QueryIntAttribute("height", &height);

        int res_width = 0;

        while (level->view->getSize().x > res_width)
            res_width += width;

        Background bg(
            //level->view->getSize().x,
            res_width,
            level->view->getSize().y,
            opacity,
            offsetx + _offsetx,
            offsety + _offsety,
            parallaxx * _parallaxx,
            parallaxy * _parallaxy,
            repeatx,
            repeaty,
            color * _color,
            PF);

        level->backgrounds.push_back(new PairBG(bg));

        e = e->NextSiblingElement("imagelayer");
    }
}

void MapParser::parseTiles(XMLElement* root) {
    /*
    ...
 <group id="71" name="tiles" locked="1">
  <layer id="1" name="background" width="68" height="31" locked="1" tintcolor="#9a9a9a">
   <data encoding="csv">
0,0,0,0,0,0,0,0,0 ...
    ...
    */

    XMLElement* g = root->Parent()->ToElement();

    float _opacity = 1.0f;
    float _offsetx = 0.f;
    float _offsety = 0.f;
    float _parallaxx = 1.0f;
    float _parallaxy = 1.0f;
    const char* _tintcolor = "#ffffffff";
    sf::Color _color(255, 255, 255, 255);

    g->QueryFloatAttribute("opacity", &_opacity);
    g->QueryFloatAttribute("offsetx", &_offsetx);
    g->QueryFloatAttribute("offsety", &_offsety);
    g->QueryFloatAttribute("parallaxx", &_parallaxx);
    g->QueryFloatAttribute("parallaxy", &_parallaxy);
    if (g->Attribute("tintcolor")) _tintcolor = g->Attribute("tintcolor");
    _color = hexToColor(_tintcolor);
    _color.a *= _opacity;

    XMLElement* e = root;

    while (e) {
        TileLayer layer;

        int width = 1;
        int height = 1;
        float opacity = 1.0f;
        float offsetx = 0.f;
        float offsety = 0.f;
        float parallaxx = 1.0f;
        float parallaxy = 1.0f;
        const char* tintcolor = "#ffffffff";
        sf::Color color(255, 255, 255, 255);
        e->QueryIntAttribute("width", &width);
        e->QueryIntAttribute("height", &height);
        e->QueryFloatAttribute("opacity", &opacity);
        e->QueryFloatAttribute("offsetx", &offsetx);
        e->QueryFloatAttribute("offsety", &offsety);
        e->QueryFloatAttribute("parallaxx", &parallaxx);
        e->QueryFloatAttribute("parallaxy", &parallaxy);

        if (e->Attribute("tintcolor")) tintcolor = e->Attribute("tintcolor");

        layer.opacity = opacity * _opacity;
        color = hexToColor(tintcolor);
        color.a *= opacity;
        layer.tintcolor = color * _color;
        layer.offsetx = offsetx + _offsetx;
        layer.offsety = offsety + _offsety;
        layer.parallaxx = parallaxx * _parallaxx;
        layer.parallaxy = parallaxy * _parallaxy;

        XMLElement* _e = e->FirstChildElement("data");
        std::vector<int> data = parseCSV(_e->GetText());

        int x = 0;
        int y = 0;
        int i = 0;
        int subToUse = 0;

        while (i < data.size()) {
            if (x == width) {
                x = 0;
                y++;
            }

            subToUse = data[i] - firstTileID;
            if (subToUse < 0) {
                x++;
                i++;
                continue;
            };

            sf::Sprite sprite;
            sprite.setTexture(*level->texture);
            sprite.setTextureRect(subRects[subToUse]);
            sprite.setPosition((float)(x * tileSize.x) + layer.offsetx, (float)(y * tileSize.y) + layer.offsety);
            sprite.setColor(layer.tintcolor);
            layer.tiles.push_back(sprite);

            x++;
            i++;
        }

        x = 0;
        y = 0;
        i = 0;

        level->layers.push_back(layer);

        e = e->NextSiblingElement("layer");
    }
}