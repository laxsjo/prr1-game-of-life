#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../types.h"
#include "files.h"
#include "str_utils.h"

typedef struct
{
    char *name;
    char *content;
} BoardSave;

void freeBoardSave(BoardSave save)
{
    free(save.name);
    free(save.content);
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

BoardState parseBoardContent(char *boardContent)
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
    lineCount++; // account for the fact that the last line might not end with a newline

    char **lines = malloc(sizeof(char *) * lineCount);
    size_t lineIndex = 0;

    size_t currentLineStartIndex = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (boardContent[i] == '\n' || i == len - 1)
        {
            size_t lineLen = i - currentLineStartIndex;
            StrSlice slice = strGetSlice(boardContent, i, lineLen);
            size_t filteredLen = strSliceCountCharOccurrences(&slice, "01");

            lines[lineIndex] = malloc(filteredLen + 1); // I should check for null here...

            // just for convenience
            char *line = lines[lineIndex];

            size_t filteredIndex = 0;
            for (size_t j = 0; j < lineLen; j++)
            {
                char current = line[currentLineStartIndex + j];
                if (current == '0' || current == '1')
                {
                    line[filteredIndex] = current;
                    filteredIndex++;
                }
            }
            line[filteredIndex] = '\0';

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

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cells[y][x] = lines[y][x] == '1';
        }
    }

    BoardState state = {
        cells,
        {width, height},
        {0, 0},
    };

    return state;
}

int loadBoard(BoardState *board, const char *saveName)
{
    FILE *fd = fopen(".gol.saves.txt", "r");
    if (fd == NULL)
    {
        return LOAD_RESULT_FILE_MISSING;
    }
    printf("worked 1\n");

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
        perror("oh nose, malloc failed!\n");
        exit(1);
    }

    fread(content, 1, len, fd);

    free(content);

    fclose(fd);

    printf("worked 2\n");

    BoardSave *boards;

    int boardLen = separateBoards(content, &boards);

    if (boardLen == 0)
    {
        return LOAD_RESULT_NAME_NOT_FOUND;
    }

    bool nameFound = false;
    BoardSave boardSave;
    for (int i = 0; i < boardLen; i++)
    {
        if (strcmp(boards[i].name, saveName) == 0)
        {
            nameFound = true;
            boardSave = boards[i];
        }
    }

    if (!nameFound)
    {
        return LOAD_RESULT_NAME_NOT_FOUND;
    }

    // parse content
    *board = parseBoardContent(boardSave.content);

    return LOAD_RESULT_SUCCESS;
}