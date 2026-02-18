#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "recompui.h"
#include "recompdata.h"
#include "z64recomp_api.h"

// Achievement rarity tiers
typedef enum {
    RARITY_COMMON = 0,
    RARITY_UNCOMMON = 1,
    RARITY_RARE = 2,
    RARITY_ULTRA_RARE = 3,
    RARITY_LEGENDARY = 4
} AchievementRarity;

// Achievement structure
typedef struct {
    u32 id;
    const char* name;
    const char* description;
    AchievementRarity rarity;
    bool unlocked;
    u32 unlock_time;
} Achievement;

// Maximum achievements
#define MAX_ACHIEVEMENTS 40

// Achievement storage
Achievement g_achievements[MAX_ACHIEVEMENTS];
u32 g_achievement_count = 0;

// UI Context
RecompuiContext g_ui_context;
RecompuiResource g_ui_root;
RecompuiResource g_ui_panel;
RecompuiResource g_ui_title;
RecompuiResource g_ui_list;
RecompuiResource g_ui_progress_label;
RecompuiResource g_ui_close_button;

// Toast notification
RecompuiContext g_toast_context;
RecompuiResource g_toast_panel;
RecompuiResource g_toast_title;
RecompuiResource g_toast_desc;
RecompuiResource g_toast_rarity;
u32 g_toast_end_time = 0;
bool g_toast_active = false;

// Menu state
bool g_menu_open = false;

// Progress tracking
u32 g_last_inventory_masks = 0;
u8 g_last_heart_pieces = 0;
u8 g_last_boss_defeated[4] = {0};

// Rarity colors (RGBA)
RecompuiColor RARITY_COLORS[] = {
    {180, 180, 180, 255}, // Common - Gray
    {100, 150, 255, 255}, // Uncommon - Blue
    {180, 100, 220, 255}, // Rare - Purple
    {255, 140, 80, 255},  // Ultra Rare - Orange
    {255, 215, 80, 255}   // Legendary - Gold
};

const char* RARITY_NAMES[] = {
    "Common",
    "Uncommon", 
    "Rare",
    "Ultra Rare",
    "Legendary"
};

const char* RARITY_ICONS[] = {
    "-",
    "*",
    "**",
    "***",
    "CROWN"
};

// ============================================
// ACHIEVEMENT DEFINITIONS
// ============================================

void define_achievements() {
    u32 id = 0;
    
    // === TRANSFORMATION MASKS ===
    g_achievements[id++] = (Achievement){id, "Deku Scrub", "Obtain the Deku Mask", RARITY_COMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Rock Sirloin", "Obtain the Goron Mask", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Guitar of Waves", "Obtain the Zora Mask", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Fierce Deity", "Obtain the Fierce Deity's Mask", RARITY_LEGENDARY, false, 0};
    
    // === UTILITY MASKS ===
    g_achievements[id++] = (Achievement){id, "Keaton Fan", "Obtain the Keaton Mask", RARITY_COMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Bunny Hop", "Obtain the Bunny Hood", RARITY_COMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Stone Cold", "Obtain the Stone Mask", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Captain's Orders", "Obtain the Captain's Hat", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Garo Guide", "Obtain the Garo Mask", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Blast Off", "Obtain the Blast Mask", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "No Sleep", "Obtain the All-Night Mask", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Giant Step", "Obtain the Giant's Mask", RARITY_ULTRA_RARE, false, 0};
    
    // === TEMPLE BOSSES ===
    g_achievements[id++] = (Achievement){id, "Jungle King", "Defeat Odolwa", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Mechanical Monster", "Defeat Goht", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Gargantuan Fish", "Defeat Gyorg", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Insectoid Duo", "Defeat Twinmold", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Majora's Fall", "Defeat Majora's Mask", RARITY_ULTRA_RARE, false, 0};
    
    // === COLLECTION ===
    g_achievements[id++] = (Achievement){id, "First Heart", "Collect your first Piece of Heart", RARITY_COMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Quarter Hearted", "Collect 13 Pieces of Heart", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Halfway There", "Collect 26 Pieces of Heart", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Heart of Gold", "Collect all 52 Pieces of Heart", RARITY_ULTRA_RARE, false, 0};
    
    // === STRAY FAIRIES ===
    g_achievements[id++] = (Achievement){id, "Woodfall Fairies", "Collect all Stray Fairies in Woodfall", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Snowhead Fairies", "Collect all Stray Fairies in Snowhead", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Great Bay Fairies", "Collect all Stray Fairies in Great Bay", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Stone Tower Fairies", "Collect all Stray Fairies in Stone Tower", RARITY_ULTRA_RARE, false, 0};
    
    // === ECONOMY ===
    g_achievements[id++] = (Achievement){id, "Big Spender", "Have 5000 Rupees in the bank", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Wallet Upgrade", "Obtain the Adult's Wallet", RARITY_COMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Giant Wallet", "Obtain the Giant's Wallet", RARITY_RARE, false, 0};
    
    // === SKULLTULA HOUSES ===
    g_achievements[id++] = (Achievement){id, "Swamp Spider", "Complete the Swamp Skulltula House", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Ocean Spider", "Complete the Ocean Skulltula House", RARITY_UNCOMMON, false, 0};
    
    // === EXTRA MASKS ===
    g_achievements[id++] = (Achievement){id, "Scents of Danger", "Obtain the Mask of Scents", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Romani's Helper", "Obtain the Romani Mask", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Troupe Leader", "Obtain the Troupe Leader's Mask", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Kafei's Mask", "Obtain Kafei's Mask", RARITY_RARE, false, 0};
    g_achievements[id++] = (Achievement){id, "Bremen March", "Obtain the Bremen Mask", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Don Gero", "Obtain Don Gero's Mask", RARITY_UNCOMMON, false, 0};
    g_achievements[id++] = (Achievement){id, "Postman Hat", "Obtain the Postman's Hat", RARITY_RARE, false, 0};
    
    g_achievement_count = id;
    recomp_printf("[Achievements] Defined %d achievements\n", g_achievement_count);
}

// ============================================
// ACHIEVEMENT CHECKING
// ============================================

bool has_mask(u32 mask_id) {
    // Check if mask is in inventory
    // Mask IDs are 0x80-0x92 in MM
    // Need to check gSaveContext.inventory.items
    return false; // TODO: Implement proper check
}

u8 get_heart_pieces() {
    // Return number of heart pieces collected
    // Stored in gSaveContext.inventory.questItems or similar
    return 0; // TODO: Implement
}

bool is_boss_defeated(u8 temple_index) {
    // Check boss defeat flags
    return false; // TODO: Implement
}

void check_achievements() {
    // Check all achievement conditions and unlock if met
    // This should be called periodically (e.g., on save load, item pickup, etc.)
    
    // TODO: Implement actual save data reading
    // For now, just placeholder
}

void unlock_achievement(u32 id) {
    if (id >= g_achievement_count) return;
    if (g_achievements[id].unlocked) return;
    
    g_achievements[id].unlocked = true;
    g_achievements[id].unlock_time = recomp_get_time_ms();
    
    recomp_printf("[Achievements] Unlocked: %s\n", g_achievements[id].name);
    
    // Show toast if enabled
    if (recomp_get_config_bool("show_toast")) {
        show_toast(id);
    }
}

// ============================================
// TOAST NOTIFICATION
// ============================================

void show_toast(u32 achievement_id) {
    if (g_toast_active) {
        // Replace current toast or queue (simplified: replace)
    }
    
    Achievement* ach = &g_achievements[achievement_id];
    float duration = recomp_get_config_double("toast_duration") * 1000.0f; // Convert to ms
    
    g_toast_end_time = recomp_get_time_ms() + (u32)duration;
    g_toast_active = true;
    
    // Update toast UI
    recompui_set_text(g_toast_title, ach->name);
    recompui_set_text(g_toast_desc, ach->description);
    recompui_set_text(g_toast_rarity, RARITY_NAMES[ach->rarity]);
    
    // Set rarity color
    recompui_set_background_color(g_toast_panel, RARITY_COLORS[ach->rarity]);
    
    // Show toast
    recompui_show_context(g_toast_context);
}

void update_toast() {
    if (!g_toast_active) return;
    
    if (recomp_get_time_ms() >= g_toast_end_time) {
        g_toast_active = false;
        recompui_hide_context(g_toast_context);
    }
}

// ============================================
// UI SETUP
// ============================================

void setup_toast_ui() {
    g_toast_context = recompui_create_context();
    recompui_open_context(g_toast_context);
    
    RecompuiResource root = recompui_context_root(g_toast_context);
    
    // Toast panel (top right)
    g_toast_panel = recompui_create_element(root, TYPE_PANEL);
    recompui_set_position(g_toast_panel, POSITION_ABSOLUTE);
    recompui_set_right(g_toast_panel, 20.0f, UNIT_DP);
    recompui_set_top(g_toast_panel, 20.0f, UNIT_DP);
    recompui_set_width(g_toast_panel, 300.0f, UNIT_DP);
    recompui_set_height(g_toast_panel, 100.0f, UNIT_DP);
    recompui_set_border_radius(g_toast_panel, 8.0f, UNIT_DP);
    
    // Title
    g_toast_title = recompui_create_element(g_toast_panel, TYPE_LABEL);
    recompui_set_text(g_toast_title, "Achievement Unlocked!");
    recompui_set_font_size(g_toast_title, 18.0f, UNIT_DP);
    recompui_set_color(g_toast_title, (RecompuiColor){255, 255, 255, 255});
    recompui_set_margin(g_toast_title, 10.0f, UNIT_DP, EDGE_ALL);
    
    // Description
    g_toast_desc = recompui_create_element(g_toast_panel, TYPE_LABEL);
    recompui_set_text(g_toast_desc, "");
    recompui_set_font_size(g_toast_desc, 14.0f, UNIT_DP);
    recompui_set_color(g_toast_desc, (RecompuiColor){220, 220, 220, 255});
    recompui_set_margin(g_toast_desc, 5.0f, UNIT_DP, EDGE_HORIZONTAL);
    
    // Rarity label
    g_toast_rarity = recompui_create_element(g_toast_panel, TYPE_LABEL);
    recompui_set_text(g_toast_rarity, "");
    recompui_set_font_size(g_toast_rarity, 12.0f, UNIT_DP);
    recompui_set_margin(g_toast_rarity, 5.0f, UNIT_DP, EDGE_ALL);
    
    recompui_close_context(g_toast_context);
    recompui_hide_context(g_toast_context);
}

void setup_menu_ui() {
    g_ui_context = recompui_create_context();
    recompui_open_context(g_ui_context);
    
    g_ui_root = recompui_context_root(g_ui_context);
    
    // Main panel (centered)
    g_ui_panel = recompui_create_element(g_ui_root, TYPE_PANEL);
    recompui_set_position(g_ui_panel, POSITION_ABSOLUTE);
    recompui_set_left(g_ui_panel, 10.0f, UNIT_PERCENT);
    recompui_set_right(g_ui_panel, 10.0f, UNIT_PERCENT);
    recompui_set_top(g_ui_panel, 10.0f, UNIT_PERCENT);
    recompui_set_bottom(g_ui_panel, 10.0f, UNIT_PERCENT);
    recompui_set_background_color(g_ui_panel, (RecompuiColor){20, 20, 30, 240});
    recompui_set_border_radius(g_ui_panel, 16.0f, UNIT_DP);
    
    // Title
    g_ui_title = recompui_create_element(g_ui_panel, TYPE_LABEL);
    recompui_set_text(g_ui_title, "Majora's Mask Achievements");
    recompui_set_font_size(g_ui_title, 28.0f, UNIT_DP);
    recompui_set_color(g_ui_title, (RecompuiColor){255, 215, 80, 255}); // Gold
    recompui_set_margin(g_ui_title, 20.0f, UNIT_DP, EDGE_ALL);
    recompui_set_align_self(g_ui_title, ALIGN_CENTER);
    
    // Progress label
    g_ui_progress_label = recompui_create_element(g_ui_panel, TYPE_LABEL);
    recompui_set_text(g_ui_progress_label, "0 / 40 Unlocked");
    recompui_set_font_size(g_ui_progress_label, 16.0f, UNIT_DP);
    recompui_set_margin(g_ui_progress_label, 10.0f, UNIT_DP, EDGE_ALL);
    
    // Close button
    g_ui_close_button = recompui_create_element(g_ui_panel, TYPE_BUTTON);
    recompui_set_text(g_ui_close_button, "Close (F2)");
    recompui_set_margin(g_ui_close_button, 20.0f, UNIT_DP, EDGE_ALL);
    recompui_set_align_self(g_ui_close_button, ALIGN_CENTER);
    
    recompui_close_context(g_ui_context);
    recompui_hide_context(g_ui_context);
}

void update_menu_ui() {
    if (!g_menu_open) return;
    
    // Update progress text
    u32 unlocked = 0;
    for (u32 i = 0; i < g_achievement_count; i++) {
        if (g_achievements[i].unlocked) unlocked++;
    }
    
    char progress_text[64];
    recomp_snprintf(progress_text, sizeof(progress_text), "%d / %d Unlocked", unlocked, g_achievement_count);
    recompui_set_text(g_ui_progress_label, progress_text);
}

void toggle_menu() {
    g_menu_open = !g_menu_open;
    
    if (g_menu_open) {
        update_menu_ui();
        recompui_show_context(g_ui_context);
    } else {
        recompui_hide_context(g_ui_context);
    }
}

// ============================================
// SAVE/LOAD
// ============================================

void save_achievements() {
    // Save achievement progress to recomp data storage
    // Using recompdata API
    for (u32 i = 0; i < g_achievement_count; i++) {
        char key[32];
        recomp_snprintf(key, sizeof(key), "ach_unlocked_%d", i);
        recomp_set_data_bool(key, g_achievements[i].unlocked);
    }
    recomp_printf("[Achievements] Progress saved\n");
}

void load_achievements() {
    // Load achievement progress from recomp data storage
    for (u32 i = 0; i < g_achievement_count; i++) {
        char key[32];
        recomp_snprintf(key, sizeof(key), "ach_unlocked_%d", i);
        g_achievements[i].unlocked = recomp_get_data_bool(key, false);
    }
    recomp_printf("[Achievements] Progress loaded\n");
}

// ============================================
// GAME HOOKS
// ============================================

RECOMP_CALLBACK("*", recomp_on_init)
void on_init() {
    recomp_printf("[Achievements] Mod initializing...\n");
    
    define_achievements();
    load_achievements();
    setup_toast_ui();
    setup_menu_ui();
    
    recomp_printf("[Achievements] Mod initialized! Press F2 for achievement menu\n");
}

RECOMP_CALLBACK("*", recomp_on_update)
void on_update() {
    // Check for F2 key to toggle menu
    // Note: Need proper input checking
    
    // Update toast timer
    update_toast();
}

RECOMP_CALLBACK("*", recomp_on_save)
void on_save() {
    save_achievements();
}

RECOMP_CALLBACK("*", recomp_on_load)
void on_load() {
    load_achievements();
    check_achievements();
}

// ============================================
// PATCHES
// ============================================

// Patch item pickup to check for mask/heart piece achievements
RECOMP_HOOK("Player_Item_Collect")
void hook_item_collect(Player* player, s32 item) {
    // Call original
    RECOMP_CALL_ORIGINAL(Player_Item_Collect, player, item);
    
    // Check for specific items
    recomp_printf("[Achievements] Item collected: %d\n", item);
    
    // Check achievements based on item
    // TODO: Map item IDs to achievement checks
}

// Example patch: Always return true for testing
// RECOMP_PATCH s32 Player_CanSpinAttack(Player* this) {
//     return true;
// }
