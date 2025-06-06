#pragma once

#include "utils.hpp"
#include "draw_scene.hpp"

void onError(int error, const char *description);
void onWindowResized(GLFWwindow *, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);