#include "Quadtree.h"

Quadtree::Quadtree(){}

Quadtree::Quadtree(glm::vec2 tl, glm::vec2 br){
  section = Rectangle(tl, br);
  sectNO = nullptr;
  sectNE = nullptr;
  sectSO = nullptr;
  sectSE = nullptr;
}

int Quadtree::addRectangleIntoSection(Rectangle r, int currentHigh){

  if (currentHigh < 1) {
    this->listRectangle.push_back(r);
    return 0;
  }


    std::vector<glm::vec2> rCorners{r.getPosUpperLeft(), r.getPosUpperRight(), r.getPosBottomLeft(), r.getPosBottomRight()};
    std::vector<bool> isAllreadyAdd = {false, false, false, false};

    float secX = (section.getPosUpperLeft().x + section.getPosBottomRight().x) / 2;
    float secY = (section.getPosUpperLeft().y + section.getPosBottomRight().y) / 2;

    for(int i = 0; i < (int)rCorners.size(); i++){
        if (rCorners[i].x <= secX){
            // Rectangle is in topLeftTree
            if (rCorners[i].y >= secY){
                if(this->sectNO == nullptr){
                    this->sectNO = new Quadtree(
                        glm::vec2(section.getPosUpperLeft().x, section.getPosUpperLeft().y),
                        glm::vec2(secX,secY)
);
                }
                if(isAllreadyAdd[0] == false){
                    this->sectNO->addRectangleIntoSection(r, currentHigh-1);
                    isAllreadyAdd[0] = true;

                }

            }
            // Rectangle is in botLeftTree
            else {
                if(this->sectSO == nullptr){
                    this->sectSO = new Quadtree(
                        glm::vec2(section.getPosUpperLeft().x, secY),
                        glm::vec2(secX, section.getPosBottomRight().y));
                }
                 if(isAllreadyAdd[1] == false){
                     this->sectSO->addRectangleIntoSection(r, currentHigh-1);
                     isAllreadyAdd[1] = true;
                 }

            }
        }
        else
        {
            // Rectangle is in topRightTree
            if ((rCorners[i].y >= secY)){
                if(this->sectNE == nullptr){
                    this->sectNE = new Quadtree(
                        glm::vec2(secX, section.getPosUpperLeft().y),
                        glm::vec2(section.getPosBottomRight().x, secY));

                }
                if(isAllreadyAdd[2] == false){
                    this->sectNE->addRectangleIntoSection(r, currentHigh-1);
                    isAllreadyAdd[2] = true;
                }
            }
            // Rectangle is in botRightTree
            else{
                if(this->sectSE == nullptr){
                    this->sectSE = new Quadtree(
                        glm::vec2(secX, secY),
                        glm::vec2(section.getPosBottomRight().x, section.getPosBottomRight().y));
                }

                if(isAllreadyAdd[3] == false){
                    this->sectSE->addRectangleIntoSection(r, currentHigh-1);
                    isAllreadyAdd[3] = true;
                }
            }
        }

    }

    return (isAllreadyAdd[0] || isAllreadyAdd[1] || isAllreadyAdd[2] || isAllreadyAdd[3]);


}

void Quadtree::drawSection(){
    this->section.draw(0);
    if(this->sectNE != NULL){
        this->sectNE->drawSection();
    }
    if(this->sectNO != NULL){
        this->sectNO->drawSection();
    }
    if(this->sectSE != NULL){
        this->sectSE->drawSection();
    }
    if(this->sectSO != NULL){
        this->sectSO->drawSection();
    }
}

bool Quadtree::isLeaf(){
    if(this->sectNO == nullptr && this->sectNE == nullptr && this->sectSE == nullptr && this->sectSO == nullptr){
        return true;
    }
    return false;

}


std::vector<Rectangle> Quadtree::search(glm::vec2 position){

    if(this->isLeaf()){
        return listRectangle;
    }

    if(this->sectNE != nullptr && this->sectNE->section.isPointInRectangle(position)){
        return this->sectNE->search(position);
    }
    if(this->sectNO != nullptr && this->sectNO->section.isPointInRectangle(position)){
        return this->sectNO->search(position);
    }
    if(this->sectSE != nullptr && this->sectSE->section.isPointInRectangle(position)){
        return this->sectSE->search(position);
    }
    if(this->sectSO != nullptr && this->sectSO->section.isPointInRectangle(position)){
        return this->sectSO->search(position);
    }

    return {};

}

std::vector<Rectangle> Quadtree::seachListRectangles(glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 botLeft, glm::vec2 botRight){
  std::vector<Rectangle> list = search(topLeft);
  std::vector<Rectangle> listTR = search(topRight);
  std::vector<Rectangle> listBL = search(botLeft);
  std::vector<Rectangle> listBR = search(botRight);
  list = addIfNotExist(list, listTR);
  list = addIfNotExist(list, listBL);
  list = addIfNotExist(list, listBR);
  return list;
}

std::vector<Rectangle> Quadtree::addIfNotExist(std::vector<Rectangle> list, std::vector<Rectangle> toAdd){
  bool t ;
    for(int i = 0; i < toAdd.size(); i++){
      t=false;
      for(int j = 0; j < list.size(); j++){
      if(list[j].getPosUpperLeft().x == toAdd[i].getPosUpperLeft().x && list[j].getPosUpperLeft().y == toAdd[i].getPosUpperLeft().y){
        t=true;
      }
    }
    if(t==false){
      list.push_back(toAdd[i]);
    }
  }
  return list;
}
