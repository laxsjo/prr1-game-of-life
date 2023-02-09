#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../types.h"
#include "files.h"
#include "str_utils.h"
#include "general.h"

typedef struct
{
    char *name;
    char *content;
} BoardSave;

typedef struct
{
    size_t nameStart;
    size_t nameLen;
    size_t contentStart;
    size_t contentLen;
} BoardLocation;

void freeBoardSave(BoardSave save)
{
    free(save.name);
    free(save.content);
}

/*
Load content of .gol.saves.txt into fileContent.

Make sure to free fileContent.

returns LOAD_RESULT_FILE_MISSING, if the file does not exist,
or LOAD_RESULT_SUCCESS on success.
*/
int readSaveFile(char **fileContent)
{
    FILE *fd = fopen(".gol.saves.txt", "r");
    if (fd == NULL)
    {
        return LOAD_RESULT_FILE_MISSING;
    }

    // get file size: https://stackoverflow.com/a/238609/15507414
    // this should probably have error cheking ;)
    fseek(fd, 0, SEEK_END);
    size_t len = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    // source: https://stackoverflow.com/a/174552/15507414
    char *content = 0;

    content = malloc(len);
    if (!content)
    {
        panic("oh nose, malloc failed!");
    }

    size_t read_items = fread(content, sizeof(char), len, fd);

    if (fclose(fd) != 0)
    {
        panic("failed to close file '.gol.saves.txt'");
    }

    *fileContent = content;
    return LOAD_RESULT_SUCCESS;
}

const char *presetFileContent =
    "[gol-text]\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0001111011110100010111001111011100100011101110111000000000000000\n"
    "0001000010010110110100001001010000100001001000100000000000000000\n"
    "0001011011110101010110001001011000100001001100110000000000000000\n"
    "0001001010010100010100001001010000100001001000100000000000000000\n"
    "0001111010010100010111001111010000111011101000111000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "[rotating-noodles]\n"
    "00000000000000000000000000000000\n"
    "00100000000000000000000000000000\n"
    "00100011100000010000000000000000\n"
    "00100000000000101000000000000000\n"
    "00000000000001000100000000000000\n"
    "00000000000000101000000000000000\n"
    "00000000000000010000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "00000000000000000000000000000000\n"
    "[glider]\n"
    "0100\n"
    "0010\n"
    "1110\n"
    "0000\n"
    "[glider-factory]\n"
    "0000000000000000000000001000000000000000000000000000000000000000\n"
    "0000000000000000000000101000000000000000000000000000000000000000\n"
    "0000000000001100000011000000000000110000000000000000000000000000\n"
    "0000000000010001000011000000000000110000000000000000000000000000\n"
    "1100000000100000100011000000000000000000000000000000000000000000\n"
    "1100000000100010110000101000000000000000000000000000000000000000\n"
    "0000000000100000100000001000000000000000000000000000000000000000\n"
    "0000000000010001000000000000000000000000000000000000000000000000\n"
    "0000000000001100000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "0000000000000000000000000000000000000000000000000000000000000000\n"
    "[horizontal-spaceship]\n"
    "00000000\n"
    "00000000\n"
    "01111000\n"
    "10001000\n"
    "00001000\n"
    "10010000\n"
    "00000000\n"
    "00000000\n"
    "[pulsar]\n" // source: https://en.wikipedia.org/wiki/File:Game_of_life_pulsar.gif
    "0000000000000000\n"
    "0001110001110000\n"
    "0000000000000000\n"
    "0100001010000100\n"
    "0100001010000100\n"
    "0100001010000100\n"
    "0001110001110000\n"
    "0000000000000000\n"
    "0001110001110000\n"
    "0100001010000100\n"
    "0100001010000100\n"
    "0100001010000100\n"
    "0000000000000000\n"
    "0001110001110000\n"
    "0000000000000000\n"
    "0000000000000000\n"
    "[random-10%]\n"
    "010100000001000000000000011000000000000001000100000001000000\n"
    "100100010000000000000100100000100000000000000010000000000010\n"
    "000010110000000000100010010000000000000000000010000000000101\n"
    "000000000001000000000000000000001010001001000000000000010000\n"
    "000010000000001000000000000010000000000000000000000000000001\n"
    "000000001000000010000000010000000100000000000000000010000000\n"
    "000000000100000000000000000010000000000010000101000001000000\n"
    "000000000000000000000001000000000000000000000000000000000001\n"
    "001010100000000000001000000000000010000000000001000000001010\n"
    "100000000000000000000000000010001101000001010000000010000000\n"
    "100000000000000000000000000000000000001000000000000000000001\n"
    "001000010000000000000000000000000000000000001000100001100000\n"
    "000000000000000000101000000000100000000000000000011000000001\n"
    "000000001000001001000000001000010011000010100101100000000001\n"
    "001010000001000010000000000010000010100100110000000100010000\n"
    "000000000000000000001000000010100000000000000000010010100000\n"
    "010000000000000000000010000000000000000000010000000001100010\n"
    "000000000000000000000000000000000100000000000000000100000000\n"
    "000000000000100000000000110000000000010000000000000000000000\n"
    "000011000000001000000000010000000010000100000000000000000000\n"
    "[random-20%]\n"
    "100000000001010000000000100000000001101000100001000000000000\n"
    "000001011110000001000000000000010000000001000000000000000010\n"
    "000010000000010101001000000000100000100010010011010001000000\n"
    "000001011100010000001000000000000011001010010000000000001000\n"
    "010001001010000000001001000000000000000000001001010000000001\n"
    "101100000000000000000000000000000101000000010100000000010000\n"
    "000000001000000001010000100100010100100000000001000010000101\n"
    "000000000100010000100000100000001101000101000000000000001100\n"
    "000000000000010001000110000000110000000000000000000100000101\n"
    "001101010000100100000011010110100011001001000110111000000000\n"
    "110000010010000000001000100000000000000100011011001111100000\n"
    "100100000001110010000000000000101001000000001000000000000100\n"
    "001001100000000000001000000100000001000001010000000000000000\n"
    "000001000100000000110000001101101010010010100010001011000100\n"
    "001001000100000000001000001001001010010001010000000001000000\n"
    "001000100000001010011001000110000000001100110000000000010000\n"
    "111100000000001000010000100000100000000010010000010000000000\n"
    "000000100000000000100100000000000000000001000000010010000000\n"
    "010000111000000000010101101001000001100000000000100100010000\n"
    "000101000100000000100000000000000000100000001000011001000000\n"
    "[random-50%]\n"
    "101110100101101111001100111110000101011110111110010100111100\n"
    "101110000100100000001011000010110110001110001110000011111101\n"
    "001100000101110100111010110111111101011111010110001011111110\n"
    "011111010111001010000000011000000010110001111111001100111110\n"
    "101001101001000111011111011001000001010101101100100100110110\n"
    "001011010110000101100000001000011110110010111101110111010111\n"
    "111001110101101000011010011000000000110010001000011011111000\n"
    "101110010111001011111110111110011011100100111000110000111011\n"
    "101010001110111111100111111111110011000001001100011000000000\n"
    "010100111001111111001010000111101000100111001011000011101010\n"
    "000111110100010001101010100111000111000011000010001011100110\n"
    "111011010111111100011101100101001111011111100001101101100001\n"
    "000100000001110110001111010000000000010010111110101010110110\n"
    "101101011001001011001100010010000001001000011011011001010111\n"
    "100100011110101110101111011101000000000000000111110111000001\n"
    "100111100110101010010110000110100010011010110001010111010001\n"
    "011000100011010100011011100100101111000100110100100100111010\n"
    "010111001101001001001101001101101101101011000110011110011101\n"
    "001100010111101101010101010000001010011011100001001110000011\n"
    "100001010000000100110010111101000000001110101100000010010101\n"
    "[random-70%]\n"
    "110010111111100100111101111011010011101111001111000101100111\n"
    "111110010111101000111101111110011101001111111010111111110100\n"
    "111110001111000111000101011110101101000111101110110111111110\n"
    "111101111001111110111100111101111011111110011111110110011010\n"
    "100011111100111000011101101111100100011101011101010111101110\n"
    "100101101101001110100001110111011101111110111111110100100111\n"
    "010001111110110011001001110011100111111100100100101111110010\n"
    "111001100110011000111011111011011011110001111110101101111111\n"
    "111111001111110111101011110011011111111111101000101101010110\n"
    "101101111111100001111100011110011101011011111111001011000001\n"
    "111000110111110111011111101110111110100111111110111111101100\n"
    "010001110011110101011100110111011111100011111111101111111101\n"
    "111110110110111111111110010101110010011111011101111101100110\n"
    "011110111110111101101011000011101111111101001010001011011001\n"
    "101111110110001010111011111101111010101101111010110111011111\n"
    "111111011111111101111111100101101100100001011011111111000111\n"
    "001100111110111011110111111011111111010111111011111111101110\n"
    "101100111111110010111111101001100001111011100111111101111101\n"
    "111011101111111011111101110101000011010000111110111110111111\n"
    "101011110001111011001000001011010101100111110101111111111011\n"
    "[random-90%]\n"
    "111111111111110111111111111111111111111111011101111011111111\n"
    "100101011111111111101111111111111111111111101111111111111011\n"
    "111011111110011110111111111111011111011110100111111110111111\n"
    "111111111111111101110111111101111011111111111111111011101111\n"
    "111111101111111111111111111101111111111111101111011011111111\n"
    "111111111011111111111111111010111101111111111110111110111110\n"
    "111111111111111111111111111111111111111111111011011111110111\n"
    "101101111111111110111111111111101111111101111111110011111111\n"
    "111011111111111111101111111101111111011111111101011111011100\n"
    "111110111111111111111110111101111111111111101111111110111111\n"
    "111111111110111111111111111111111111011101110111011100111111\n"
    "011111011001111111111111111111111111111101111111111111011111\n"
    "101111111111101101111111111111000110111111111111101111101110\n"
    "111111111111111111111111101111111111111101111111111111111111\n"
    "111111111111001111111111110111101111110111111111111111111111\n"
    "111110111111111111111101110111111111111111111110111111101111\n"
    "110111111111111111111111111111111110111111111111111111111111\n"
    "111111110111100111111111111111111111111111111111011111101111\n"
    "110111111011110111111010111111111111111111111111111111111011\n"
    "111111111111111111111111111111110111111111111111111101111111\n";

/*
Load content of preset 'file' into fileContent.

Make sure to free fileContent.
Always succeeds.
*/
void readPresetFile(char **fileContent)
{

    size_t len = strlen(presetFileContent);

    *fileContent = malloc(len + 1);
    strcpy(*fileContent, presetFileContent);
}

void writeSaveFile(const char *content)
{
    FILE *fd = fopen(".gol.saves.txt", "w");
    if (fd == NULL)
    {
        panic("opening file '.gol.saves.txt' failed");
    }

    size_t len = strlen(content);

    fwrite(content, 1, len, fd);

    if (fclose(fd) != 0)
    {
        panic("failed to close file '.gol.saves.txt'");
    }
}

int separateBoards(const char *fileContent, BoardSave **boardList)
{
    int len = strlen(fileContent);

    // find board count
    int nameCount = 0;
    {
        bool searchingName = false;

        for (int i = 0; i < len; i++)
        {
            char current = fileContent[i];
            if (current == '[')
            {
                searchingName = true;
            }

            if (current == ']' && searchingName)
            {
                searchingName = false;
                nameCount++;
            }
        }
    }

    if (nameCount == 0)
    {
        *boardList = NULL;
        return 0;
    }

    // allocate output list
    *boardList = malloc(sizeof(BoardSave) * nameCount);

    BoardSave *out = *boardList;

    {
        int boardIndex = 0;
        BoardSave currentBoard = {
            NULL,
            NULL,
        };

        int nameStartIndex = 0;
        bool searchingName = false;

        int contentStartIndex = 0;
        bool searchingContent = false;
        for (int i = 0; i < len; i++)
        {
            char current = fileContent[i];
            if (current == '[')
            {
                searchingName = true;
                nameStartIndex = i + 1;

                if (searchingContent)
                {
                    int boardLen = i - contentStartIndex;
                    currentBoard.content = malloc(boardLen + 1);

                    memcpy(currentBoard.content, fileContent + contentStartIndex, boardLen);
                    currentBoard.content[boardLen] = '\0';

                    out[boardIndex] = currentBoard;
                    boardIndex++;

                    searchingContent = false;
                }
            }

            if (current == ']' && searchingName)
            {
                searchingContent = true;
                contentStartIndex = i + 1;

                int nameLen = i - nameStartIndex;
                currentBoard.name = malloc(nameLen + 1);

                memcpy(currentBoard.name, fileContent + nameStartIndex, nameLen);
                currentBoard.name[nameLen] = '\0';

                searchingName = false;
            }
        }

        if (searchingContent)
        {
            int boardLen = len - contentStartIndex;
            currentBoard.content = malloc(boardLen + 1);

            memcpy(currentBoard.content, fileContent + contentStartIndex, boardLen);
            currentBoard.content[boardLen] = '\0';

            out[boardIndex] = currentBoard;
        }
    }

    return nameCount;
}

BoardState parseBoardContent(const char *boardContent)
{
    size_t len = strlen(boardContent);
    // count lines
    int lineCount = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (boardContent[i] == '\n')
        {
            lineCount++;
        }
    }
    if (boardContent[len - 1] != '\n')
    {
        lineCount++; // account for the fact that the last line might not end with a newline
    }

    char **lines = malloc(sizeof(char *) * lineCount);
    size_t lineIndex = 0;

    size_t currentLineStartIndex = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (boardContent[i] == '\n' || i == len - 1)
        {
            if (i == len - 1 && boardContent[i] != '\n')
            {
                i++;
            }
            size_t lineLen = i - currentLineStartIndex;
            StrSlice slice = strGetSlice(boardContent, currentLineStartIndex, lineLen);
            size_t filteredLen = strSliceCountCharOccurrences(&slice, "01");

            char *line = lines[lineIndex];
            lines[lineIndex] = malloc(filteredLen + 1);
            if (lines[lineIndex] == NULL)
            {
                panic("oh nose, malloc failed!");
            }
            lines[lineIndex][filteredLen] = '\0';

            // just for convenience

            size_t filteredIndex = 0;
            for (size_t j = 0; j < lineLen; j++)
            {
                char current = boardContent[currentLineStartIndex + j];
                if (current == '0' || current == '1')
                {
                    lines[lineIndex][filteredIndex] = current;
                    filteredIndex++;
                }
            }

            lineIndex++;
            currentLineStartIndex = i + 1;
        }
    }

    // find line (that isn't blank) with minimum width
    size_t width = __SIZE_MAX__;
    size_t height = 0;
    for (size_t i = 0; i < lineCount; i++)
    {
        size_t len = strlen(lines[i]);
        if (len == 0)
        {
            continue;
        }
        height++;

        if (len < width)
        {
            width = len;
        }
    }

    // allocate cells
    bool **cells = malloc(sizeof(bool *) * height);
    for (int i = 0; i < height; i++)
    {
        cells[i] = malloc(sizeof(bool) * width);
    }

    size_t y = 0;
    for (size_t i = 0; i < lineCount; i++)
    {
        if (strlen(lines[i]) == 0)
        {
            continue;
        }
        for (size_t x = 0; x < width; x++)
        {
            cells[y][x] = lines[i][x] == '1';
        }
        y++;
    }
    // printf("lineCount: %i\nwidth: %lu, height: %lu\n", lineCount, width, height);
    for (size_t i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }
    free(lines);

    BoardState state = {
        cells,
        {width, height},
        {0, 0},
    };

    return state;
}

void createFileContentFromBoardList(char **fileContent, const BoardSave *boardList, const size_t listLen)
{
    size_t totalLen = 0;
    for (size_t i = 0; i < listLen; i++)
    {
        size_t nameLen = strlen(boardList[i].name);
        size_t contentLen = strlen(boardList[i].content);
        contentLen += boardList[i].content[0] != '\n';
        contentLen += boardList[i].content[contentLen - 1] != '\n';

        totalLen += nameLen + 2 + contentLen; // = ['nameLen']'contentLen'
    }

    char *content = malloc(totalLen + 1);
    content[totalLen] = '\0';

    size_t index = 0;

    for (size_t i = 0; i < listLen; i++)
    {
        // potential optimization: store these in a list, to avoid duplicate calculation.
        size_t nameLen = strlen(boardList[i].name);
        size_t contentLen = strlen(boardList[i].content);

        content[index++] = '[';
        memcpy(content + index, boardList[i].name, nameLen);
        index += nameLen;
        content[index++] = ']';

        if (boardList[i].content[0] != '\n')
        {
            content[index++] = '\n';
        }
        memcpy(content + index, boardList[i].content, contentLen);
        index += contentLen;
        if (boardList[i].content[contentLen - 1] != '\n')
        {
            content[index++] = '\n';
        }
    }

    *fileContent = content;
}

/* Load board save of name saveName from the .gol.saves.txt save file.
Returns LOAD_RESULT_*
Make sure you check for errors!
*/
int loadBoard(BoardState *board, const char *saveName, const bool isPreset)
{
    char *content;
    if (!isPreset)
    {
        int result = readSaveFile(&content);
        if (result == LOAD_RESULT_FILE_MISSING)
        {
            return LOAD_RESULT_FILE_MISSING;
        }
    }
    else
    {
        readPresetFile(&content);
    }

    BoardSave *boardSaves;

    int boardLen = separateBoards(content, &boardSaves);

    if (boardLen == 0)
    {
        return LOAD_RESULT_NAME_NOT_FOUND;
    }

    bool nameFound = false;
    BoardSave boardSave;
    for (int i = 0; i < boardLen; i++)
    {
        if (strcmp(boardSaves[i].name, saveName) == 0)
        {
            nameFound = true;
            boardSave = boardSaves[i];
        }
    }

    if (!nameFound)
    {
        return LOAD_RESULT_NAME_NOT_FOUND;
    }

    // parse content
    *board = parseBoardContent(boardSave.content);
    board->isPreset = isPreset;
    board->shouldSave = !isPreset;

    for (size_t i = 0; i < boardLen; i++)
    {
        freeBoardSave(boardSaves[i]);
    }

    free(content);
    return LOAD_RESULT_SUCCESS;
}

void saveBoard(const BoardState *state)
{
    char *content = "";
    readSaveFile(&content);

    BoardSave *boardSaves;

    int boardLen = separateBoards(content, &boardSaves);
    free(content);

    bool nameFound = false;
    BoardSave *boardSave;
    for (int i = 0; i < boardLen; i++)
    {
        if (strcmp(boardSaves[i].name, state->saveName) == 0)
        {
            nameFound = true;
            boardSave = &boardSaves[i];
        }
    }

    if (!nameFound)
    {
        // resize boardSaves
        /* Problem: malloc returned weird error "malloc(): invalid size
        (unsorted)"
        The problem was that the newly allocated list was of the wrong size, which
        caused funky memory behaviour, causing malloc to fail for whatever
        reason.
        Basically it was
        `malloc(sizeof(newBoardSaves) + 1)`
        but it should have been:
        `malloc(sizeof(*newBoardSaves) * (boardLen + 1))`

        source: https://linux.die.net/man/3/malloc

        I also forgot to free the old boardSaves list, but that didn't really
        cause any issuse other than leaking memory.
        */
        BoardSave *newBoardSaves = malloc(sizeof(*newBoardSaves) * (boardLen + 1));
        for (int i = 0; i < boardLen; i++)
        {
            newBoardSaves[i] = boardSaves[i];
        }
        boardLen += 1;
        free(boardSaves);
        boardSaves = newBoardSaves;

        boardSaves[boardLen - 1] = (BoardSave){state->saveName, NULL};
        boardSave = &boardSaves[boardLen - 1];
    }

    size_t width = state->screenSize.x;
    size_t height = state->screenSize.y;

    size_t boardContentLen = width * height + height; // cells + 1 newline per line

    char *boardContent = malloc(boardContentLen + 1);
    boardContent[boardContentLen] = '\0';

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            char current;
            if (state->cells[y][x] == true)
            {
                current = '1';
            }
            else
            {
                current = '0';
            }
            boardContent[y * (width + 1) + x] = current;
        }
        boardContent[y * (width + 1) + width] = '\n';
    }

    boardSave->content = boardContent;

    char *newContent;
    createFileContentFromBoardList(&newContent, boardSaves, boardLen);

    // printf("wrote new content:\n%s", newContent);

    writeSaveFile(newContent);
    free(newContent);
}

size_t getAvailableSaveNames(char ***names, const bool getPresetNames)
{
    char *content;

    if (getPresetNames)
    {
        readPresetFile(&content);
    }
    else
    {
        int result = readSaveFile(&content);

        if (result == LOAD_RESULT_FILE_MISSING)
        {
            *names = malloc(0);
            return 0;
        }
    }

    BoardSave *saves;

    int len = separateBoards(content, &saves);
    free(content);

    char **out = malloc(sizeof(*names) * len);

    // if (len = 0)
    // {
    //     names = malloc(0);
    //     return 0;
    // }

    for (size_t i = 0; i < len; i++)
    {
        out[i] = saves[i].name;
        free(saves[i].content);
    }

    free(saves);
    *names = out;
    return len;
}
