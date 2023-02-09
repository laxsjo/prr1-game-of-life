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

/*
Load content of preset 'file' into fileContent.

Make sure to free fileContent.
Always succeeds.
*/
void readPresetFile(char **fileContent)
{
    const char *presetFileContent =
        "[preset1]\n"
        "0000000000\n"
        "0000000100\n"
        "0011100100\n"
        "0000000100\n"
        "0000000000\n"
        "[glider]\n"
        "000000000000000000000000\n"
        "001000000000000000000000\n"
        "000100000000000000000000\n"
        "011100000000000000000000\n"
        "000000000000000000000000\n"
        "000000000000000000000000\n"
        "000000000000000000000000\n"
        "000000000000000000000000\n"
        "000000000000000000000000\n";

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
