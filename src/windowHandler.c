/***************************************************************
*                      Author: Eric Llaca                      *
*                      Source Language: c                      *
*                                                              *
*                   --- Code Description ---                   *
*                     _            _            _              *
*                    | |          | |          | |             *
*                    | | _  _ __  | | _____  __| |             *
*        888         | || || '_ \ | |/ / _ \/ _` |             *
*        888         | || || | | ||   <  __/ (_| |             *
*        888         |_||_||_| |_||_|\_\___|\__,_|             *
*    .d88888888  88888888b.  .d88b.  .d88b.  .d88b. 88888b.    *
*   d88" 888888  888888 "88bd88P"88bd8P  Y8bd88""88b888 "88b   *
*   888  888888  888888  888888  88888888888888  888888  888   *
*   Y88b 888Y88b 888888  888Y88b 888Y8b.    Y88..88P888  888   *
*    "Y88888 "Y88888888  888 "Y88888 "Y8888  "Y88P" 888  888   *
*                                888                           *
*                           Y8b d88P                           *
*                            "Y88P"                            *
***************************************************************/

#include <linked_dungeons.h>

void	windowLoop(int gameScreenWidth, int gameScreenHeight, RenderTexture2D target, Color *colors)
{
	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

	Texture2D test = LoadTexture("assets/enemyWalking_2.png");

	while(!WindowShouldClose())
	{
	// Update
        //----------------------------------------------------------------------------------
        // Compute required framebuffer scaling
		float scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);
	// Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
		BeginTextureMode(target);
            ClearBackground(RAYWHITE);  // Clear render texture background color

            for (int i = 0; i < 10; i++) DrawRectangle(0, (gameScreenHeight/10)*i, gameScreenWidth, gameScreenHeight/10, colors[i]);

            DrawText("linkedDungeons", 10, 25, 20, WHITE);
			DrawTexture(test, 0, 0, WHITE);
        EndTextureMode();

		BeginDrawing();
            ClearBackground(BLACK);     // Clear screen background
			DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                           (float)gameScreenWidth*scale, (float)gameScreenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
	}
}

void	textureInit()
{
	int gameScreenWidth = 640;
    int gameScreenHeight = 480;

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    //SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

    Color colors[10] = { 0 };
    for (int i = 0; i < 10; i++) colors[i] = (Color){ GetRandomValue(100, 250), GetRandomValue(50, 150), GetRandomValue(10, 100), 255 };
	
	windowLoop(gameScreenWidth, gameScreenHeight, target, colors);
}

void	setWindow(int winW, int winH)
{
	const int windowWidth = winW;
    const int windowHeight = winH;

	// Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(windowWidth, windowHeight, "linkedDungeons");
    SetWindowMinSize(320, 240);

	textureInit();
	CloseWindow();
}