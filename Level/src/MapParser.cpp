#include "MapParser.hpp"
#include "Level.hpp"

using namespace tinyxml2;

std::vector<int> parseCSV(std::string str) {
    std::vector<int> vect;

    std::stringstream ss(str);

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return vect;
}

std::vector<Point> parsePoints(std::string string) {
    std::vector<Point> res;
    std::stringstream ss(string);

    while (ss.peek() != EOF) {
        Point point;
        ss >> point.x;
        ss.ignore();
        ss >> point.y;
        res.push_back(point);
    }

    return res;
}

sf::Color hexToColor(const char* hexstring) {
    uint32_t hexdec;
    std::stringstream ss(hexstring);
    if (ss.peek() == '#') ss.ignore();
    ss >> std::hex >> hexdec;

    unsigned int r, g, b, a;
    unsigned int bitmask = 255;

    if (((hexdec >> 24) & bitmask) > 0) {

        b = (hexdec >> 0) & bitmask;
        g = (hexdec >> 8) & bitmask;
        r = (hexdec >> 16) & bitmask;
        a = (hexdec >> 24) & bitmask;
    }
    else {
        b = (hexdec & bitmask);
        g = (hexdec >> 8) & bitmask;
        r = (hexdec >> 16) & bitmask;
        a = 255;
    }

    return sf::Color(r, g, b, a);
}

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

    XMLElement* e = root;

    while (e) {
        int id;
        float x;
        float y;
        float width;
        float height;
        std::string type;
        int gid;

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

        /*
        level->backgrounds.push_back(
            new Background(
                level->view->getSize().x,
                level->view->getSize().y,
                opacity,
                offsetx,
                offsety,
                parallaxx,
                parallaxy,
                repeatx,
                repeaty,
                color,
                PF
            ));
        */

        Background bg(
            //level->view->getSize().x,
            res_width,
            level->view->getSize().y,
            opacity,
            offsetx,
            offsety,
            parallaxx,
            parallaxy,
            repeatx,
            repeaty,
            color,
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

        layer.opacity = opacity;
        color = hexToColor(tintcolor);
        color.a = (int)(color.a * opacity);
        layer.tintcolor = color;
        layer.offestx = offsetx;
        layer.offsety = offsety;
        layer.parallaxx = parallaxx;
        layer.parallaxy = parallaxy;


        XMLElement* _e = e->FirstChildElement("data");
        std::vector<int> data = parseCSV(_e->GetText());

        int x = 0;
        int y = 0;
        int i = 0;

        while (i < data.size()) {
            if (x == width) {
                x = 0;
                y++;
            }
            int subToUse = 0;
            subToUse = data[i] - firstTileID;
            if (subToUse < 0) subToUse = 0;

            sf::Sprite sprite;
            sprite.setTexture(*level->texture);
            sprite.setTextureRect(subRects[subToUse]);
            sprite.setPosition((float)(x * tileSize.x) + offsetx, (float)(y * tileSize.y) + offsety);
            sprite.setColor(color);
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