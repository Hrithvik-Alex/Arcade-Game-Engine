//
// Created by Hrithvik  Alex on 2020-04-12.
//

#include "BreakoutGameLevel.h"
#include "Block.h"
#include "Ball.h"
#include "../../App/App.h"
#include "../../Utils/FileCommandLoader.h"


BreakoutGameLevel::BreakoutGameLevel(){

}

void BreakoutGameLevel::init(const Rectangle& boundary){
    createDefaultLevel(boundary);
}

void BreakoutGameLevel::load(const std::vector<Block>& blocks){
    mBlocks.clear();
    mBlocks = blocks;
}

void BreakoutGameLevel::update(uint32_t dt, Ball& ball){
    std::vector<Block> collidedBlocks;

    BoundaryEdge edgeToBounceOff;
    Block* blockBouncePtr = nullptr;

    float largestMag = -1.0f;
    for(auto& block: mBlocks) {
        BoundaryEdge edge;

        if(!block.isDestroyed() && block.hasCollided(ball.getBoundingRect(), edge)) {
            collidedBlocks.push_back(block);

            float mag = block.getCollisionOffset(ball.getBoundingRect()).Mag();
            if(mag > largestMag) {
                edgeToBounceOff = edge;
                blockBouncePtr = &block;
                largestMag = mag;
            }
        }
    }
    if(blockBouncePtr != nullptr) {
        blockBouncePtr->bounce(ball, edgeToBounceOff);
        blockBouncePtr->reduceHP();
    }

    for(const auto& block : collidedBlocks) {
        BoundaryEdge edge;
        if(block.hasCollided(ball.getBoundingRect(), edge)) {
            Vec2D p;
            ball.makeFlushWithEdge(edge, p, true);
        }
    }

}

void BreakoutGameLevel::draw(Screen& screen){
    for(auto& block: mBlocks) {
        if(!block.isDestroyed()) {
            block.draw(screen);
        }
    }
}

void BreakoutGameLevel::createDefaultLevel(const Rectangle& boundary) {
    mBlocks.clear();

    const int NUM_BLOCKS_ACROSS = ((int)boundary.getWidth() - (2*BLOCK_WIDTH))/BLOCK_WIDTH;
    const int NUM_BLOCK_ROWS = 5;

    float startX = ((int)boundary.getWidth() - (NUM_BLOCKS_ACROSS * (BLOCK_WIDTH+1)))/2;

    Color colors[NUM_BLOCK_ROWS];
    colors[0] = Color::Red();
    colors[1] = Color::Magenta();
    colors[2] = Color::Yellow();
    colors[3] = Color::Green();
    colors[4] = Color::Cyan();

    for(int r = 0; r < NUM_BLOCK_ROWS; ++r) {

        Rectangle blockRect = {Vec2D(startX, BLOCK_HEIGHT * (r+1)), BLOCK_WIDTH, BLOCK_HEIGHT};
        for (int c = 0; c < NUM_BLOCKS_ACROSS; ++c) {
            Block b;
            b.init(blockRect, 1, Color::Black(), colors[r]);
            mBlocks.push_back(b);
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    }

}

bool BreakoutGameLevel::isLevelComplete() const {
    for(size_t i = 0; i < mBlocks.size(); ++i) {
        if(!mBlocks[i].isDestroyed() && mBlocks[i].getHP() != Block::UNBREAKABLE) {
            return false;
        }
    }
    return true;
}


struct LayoutBlock {
    char symbol = '-';
    int hp = 0;
    Color color = Color::Black();
};

LayoutBlock findLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol) {

    for (size_t i = 0; i < blocks.size(); ++i) {
        if(blocks[i].symbol == symbol) {
            return blocks[i];
        }
    }

    return LayoutBlock();
}

std::vector<BreakoutGameLevel> BreakoutGameLevel::LoadLevelsFromFile(const std::string& filePath) {

    std::vector<BreakoutGameLevel> levels;
    std::vector<LayoutBlock> layoutBlocks;
    std::vector<Block> levelBlocks;

    int width = 0;
    int height = 0;

    FileCommandLoader fileLoader;

    Command levelCommand;
    levelCommand.command = "level";
    levelCommand.parseFunc = [&](ParseFuncParams params)  {
        if(levels.size() > 0) {
            levels.back().load(levelBlocks);
        }
        layoutBlocks.clear();
        levelBlocks.clear();
        width = 0;
        height = 0;

        BreakoutGameLevel level;
        level.init(Rectangle(Vec2D::Zero, App::Singleton().width(), App::Singleton().height()));
        levels.push_back(level);
    };

    fileLoader.addCommand(levelCommand);

    Command blockCommand;
    blockCommand.command = "block";
    blockCommand.parseFunc = [&](ParseFuncParams) {
        LayoutBlock lb;
        layoutBlocks.push_back(lb);
    };

    fileLoader.addCommand(blockCommand);

    Command symbolCommand;
    symbolCommand.command = "symbol";
    symbolCommand.parseFunc = [&](ParseFuncParams params) {
        layoutBlocks.back().symbol = FileCommandLoader::readChar(params);
    };

    fileLoader.addCommand(symbolCommand);

    Command fillColorCommand;
    fillColorCommand.command = "fillcolor";
    fillColorCommand.parseFunc = [&](ParseFuncParams params) {
        layoutBlocks.back().color = FileCommandLoader::readColor(params);
    };

    fileLoader.addCommand(fillColorCommand);

    Command hpCommand;
    hpCommand.command = "hp";
    hpCommand.parseFunc = [&](ParseFuncParams params) {
        layoutBlocks.back().hp = FileCommandLoader::readInt(params);
    };

    fileLoader.addCommand(hpCommand);

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseFuncParams params) {
        width = FileCommandLoader::readInt(params);
    };

    fileLoader.addCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseFuncParams params) {
        height = FileCommandLoader::readInt(params);
    };

    fileLoader.addCommand(heightCommand);

    Command layoutCommand;
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.command = "layout";
    layoutCommand.parseFunc = [&](ParseFuncParams params) {
        int blockWidth = blockWidth;
        int screenWidth = App::Singleton().width();

        float startingX = 0;
        Rectangle blockRect(Vec2D(startingX, (params.lineNum+1)*BLOCK_HEIGHT),BLOCK_WIDTH,BLOCK_HEIGHT);
        for(int c = 0; c < params.line.length();++c) {
            if( params.line[c]!= '-') {
                LayoutBlock layoutBlock = findLayoutBlockForSymbol(layoutBlocks, params.line[c]);
                Block b;
                b.init(blockRect, layoutBlock.hp, Color::Black(), layoutBlock.color);
                levelBlocks.push_back(b);
            }
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    };

    fileLoader.addCommand(layoutCommand);

    fileLoader.loadFile(filePath);

    if(levels.size() > 0) {
        levels.back().load(levelBlocks);
    }

    return levels;
}