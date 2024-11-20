#ifndef ROUTES_HPP
#define ROUTES_HPP

#include "Display.hpp"
#include "Menu.hpp"
#include "EditMsgMenu.hpp"
#include "ShowMsgMenu.hpp"

class Navigator {
public:
    // IDs dos menus
    enum MenuID {
        SHOW_MSG_MENU,
        EDIT_MSG_MENU
    };

    // Menus globais
    static EditMsgMenu editMsgMenu;
    static ShowMsgMenu showMsgMenu;

    // Variável global para o menu selecionado
    static Menu* selectedMenu;

    // Função de Navegação
    static void navigateTo(MenuID menu_id) {
        switch (menu_id) {
            case SHOW_MSG_MENU:
                selectedMenu = &showMsgMenu;
                break;

            case EDIT_MSG_MENU:
                selectedMenu = &editMsgMenu;
                break;
        }
    }
};

// Definição de variáveis estáticas
EditMsgMenu Navigator::editMsgMenu(&display); // Supõe-se que "display" exista em outro lugar.
ShowMsgMenu Navigator::showMsgMenu(&display);
Menu* Navigator::selectedMenu = nullptr;

#endif // !ROUTES_HPP
