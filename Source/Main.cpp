// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

#include "OSGSplitPanel.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGUIFont.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"
#include "OSGPolygonUIDrawObject.h"
#include "OSGUIDrawObjectCanvas.h"

#include "OSGTree.h"
#include "OSGComponentTreeModel.h"
#include "OSGScrollPanel.h"
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

MenuBarTransitPtr createMenuBar(void);
PanelTransitPtr   createToolBar(void);
PanelTransitPtr   createNavigationPanel(void);
PanelTransitPtr   createPalletePanel(void);
PanelTransitPtr   createPropertiesPanel(void);
PanelTransitPtr   createEditorPanel(void);
PanelTransitPtr   createStatusBarPanel(void);
InternalWindowTransitPtr   createEditorWindow(void);

/******************************************************

  Create an Action to display text
  in the Console Window when the Button is
  pressed (causing an action).

 ******************************************************/

void actionPerformed(ActionEventDetails* const details)
{
    std::cout << "Button 1 Action" << std::endl;
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        InternalWindowRecPtr MainInternalWindow = createEditorWindow();

        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "04UIBuilder");

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

MenuBarTransitPtr createMenuBar(void)
{
    MenuItemRecPtr NewMenuItem = MenuItem::create();
    MenuItemRecPtr SaveMenuItem = MenuItem::create();
    MenuItemRecPtr SaveAsMenuItem = MenuItem::create();
    MenuItemRecPtr OpenMenuItem = MenuItem::create();
    MenuItemRecPtr CloseMenuItem = MenuItem::create();
    MenuItemRecPtr ExitMenuItem = MenuItem::create();

    MenuItemRecPtr UndoMenuItem = MenuItem::create();
    MenuItemRecPtr RedoMenuItem = MenuItem::create();

    //Edits MenuItems
    NewMenuItem->setText("New ...");
    NewMenuItem->setAcceleratorKey(KeyEventDetails::KEY_N);
    NewMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    NewMenuItem->setMnemonicKey(KeyEventDetails::KEY_N);

    SaveMenuItem->setText("Save ...");
    SaveMenuItem->setAcceleratorKey(KeyEventDetails::KEY_S);
    SaveMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    SaveMenuItem->setMnemonicKey(KeyEventDetails::KEY_P);

    SaveAsMenuItem->setText("Save As ...");
    SaveAsMenuItem->setAcceleratorKey(KeyEventDetails::KEY_S);
    SaveAsMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND
                                            |
                                            KeyEventDetails::KEY_MODIFIER_SHIFT);
    SaveAsMenuItem->setMnemonicKey(KeyEventDetails::KEY_P);

    OpenMenuItem->setText("Open ...");
    OpenMenuItem->setAcceleratorKey(KeyEventDetails::KEY_P);
    OpenMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    OpenMenuItem->setMnemonicKey(KeyEventDetails::KEY_P);

    CloseMenuItem->setText("Close ...");
    CloseMenuItem->setAcceleratorKey(KeyEventDetails::KEY_W);
    CloseMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    CloseMenuItem->setMnemonicKey(KeyEventDetails::KEY_C);

    ExitMenuItem->setText("Quit");
    ExitMenuItem->setAcceleratorKey(KeyEventDetails::KEY_Q);
    ExitMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    ExitMenuItem->setMnemonicKey(KeyEventDetails::KEY_Q);

    UndoMenuItem->setText("Undo");
    UndoMenuItem->setAcceleratorKey(KeyEventDetails::KEY_Z);
    UndoMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    UndoMenuItem->setMnemonicKey(KeyEventDetails::KEY_U);
    RedoMenuItem->setText("Redo");
    RedoMenuItem->setEnabled(false);
    RedoMenuItem->setMnemonicKey(KeyEventDetails::KEY_R);

    // Create a File menu and adds its MenuItems
    MenuRecPtr FileMenu = Menu::create();
    FileMenu->addItem(NewMenuItem);
    FileMenu->addItem(OpenMenuItem);
    FileMenu->addItem(CloseMenuItem);
    FileMenu->addSeparator();
    FileMenu->addItem(SaveMenuItem);
    FileMenu->addItem(SaveAsMenuItem);
    FileMenu->addSeparator();
    FileMenu->addItem(ExitMenuItem);
     
    // Labels the File Menu
    FileMenu->setText("File");
    FileMenu->setMnemonicKey(KeyEventDetails::KEY_F);

    // Creates an Edit menu and adds its MenuItems
    MenuRecPtr EditMenu = Menu::create();
    EditMenu->addItem(UndoMenuItem);
    EditMenu->addItem(RedoMenuItem);

    // Labels the Edit Menu
    EditMenu->setText("Edit");
    EditMenu->setMnemonicKey(KeyEventDetails::KEY_E);

    //Main Menu Bar
    MenuBarRecPtr MainMenuBar = MenuBar::create();
    MainMenuBar->addMenu(FileMenu);
    MainMenuBar->addMenu(EditMenu);

    return MenuBarTransitPtr(MainMenuBar);
}

PanelTransitPtr   createToolBar(void)
{
    //Buttons
    Vec2f ToolButtonSize(40.0f,40.0f);

    ButtonRecPtr OpenButton = Button::create();
    OpenButton->setPreferredSize(ToolButtonSize);

    ButtonRecPtr SaveButton = Button::create();
    SaveButton->setPreferredSize(ToolButtonSize);

    ButtonRecPtr UndoButton = Button::create();
    UndoButton->setPreferredSize(ToolButtonSize);

    ButtonRecPtr RedoButton = Button::create();
    RedoButton->setPreferredSize(ToolButtonSize);

    //Layout
    FlowLayoutRecPtr ToolBarLayout = FlowLayout::create();
    ToolBarLayout->setHorizontalGap(2.0f);
    ToolBarLayout->setVerticalGap(2.0f);
    ToolBarLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
    ToolBarLayout->setMajorAxisAlignment(0.0f);
    ToolBarLayout->setMinorAxisAlignment(0.5f);

    //Main Panel
    PanelRecPtr Result = Panel::createEmpty();
    Result->pushToChildren(OpenButton);
    Result->pushToChildren(SaveButton);
    Result->pushToChildren(UndoButton);
    Result->pushToChildren(RedoButton);
    Result->setLayout(ToolBarLayout);
    Result->setPreferredSize(Vec2f(1.0f, 42.0f));
    Result->setInset(Vec4f(2.0f, 2.0f, 0.0f, 0.0f));

    return PanelTransitPtr(Result);
}

PanelTransitPtr   createNavigationPanel(void)
{
    PanelRecPtr NavigationPanel = Panel::createEmpty();

    //Create the Tree
    TreeRecPtr TheTree = Tree::create();

    ComponentTreeModelRecPtr TheTreeModel = ComponentTreeModel::create();
    TheTreeModel->setRoot(NavigationPanel);

    TheTree->setModel(TheTreeModel);
    TheTree->setRootVisible(true);

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setViewComponent(TheTree);

    //Layout
    BorderLayoutRecPtr NavigatorLayout = BorderLayout::create();

    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    ExampleScrollPanel->setConstraints(CenterConstraints);

    NavigationPanel->setLayout(NavigatorLayout);
    NavigationPanel->pushToChildren(ExampleScrollPanel);

    return PanelTransitPtr(NavigationPanel);
}

PanelTransitPtr   createPalletePanel(void)
{
    PanelRecPtr Result = Panel::createEmpty();
    return PanelTransitPtr(Result);
}

PanelTransitPtr   createPropertiesPanel(void)
{
    PanelRecPtr Result = Panel::createEmpty();
    return PanelTransitPtr(Result);
}

PanelTransitPtr   createEditorPanel(void)
{
    PanelRecPtr Result;
    return PanelTransitPtr(Result);
}

PanelTransitPtr   createStatusBarPanel(void)
{
    LabelRecPtr StatusLabel = Label::create();
    StatusLabel->setText("Status");

    //Layout
    BorderLayoutRecPtr StatusLayout = BorderLayout::create();

    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    StatusLabel->setConstraints(CenterConstraints);

    PanelRecPtr Result = Panel::createEmpty();
    Result->setLayout(StatusLayout);
    Result->pushToChildren(StatusLabel);
    Result->setPreferredSize(Vec2f(1.0f, 22.0f));
    return PanelTransitPtr(Result);
}

InternalWindowTransitPtr   createEditorWindow(void)
{
    MenuBarRecPtr MainMenuBar     = createMenuBar();
    PanelRecPtr   ToolBarPanel    = createToolBar();
    PanelRecPtr   NavigationPanel = createNavigationPanel();
    PanelRecPtr   PalletePanel    = createPalletePanel();
    PanelRecPtr   PropertiesPanel = createPropertiesPanel();
    PanelRecPtr   EditorPanel     = createEditorPanel();
    PanelRecPtr   StatusBarPanel  = createStatusBarPanel();

    //Properties and Pallete Panel
    SplitPanelRecPtr PropPalletePanel = SplitPanel::create();
    PropPalletePanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
    PropPalletePanel->setDividerPosition(0.5f); 
    PropPalletePanel->setMinComponent(PalletePanel);
    PropPalletePanel->setMaxComponent(PropertiesPanel);

    //Main Editor Panel
    SplitPanelRecPtr SubEditorPanel = SplitPanel::create();
    SubEditorPanel->setDividerPosition(0.75f); 
    SubEditorPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
    SubEditorPanel->setMinComponent(EditorPanel);
    SubEditorPanel->setMaxComponent(PropPalletePanel);

    SplitPanelRecPtr MainEditorPanel = SplitPanel::create();
    MainEditorPanel->setDividerPosition(0.25f); 
    MainEditorPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
    MainEditorPanel->setMinComponent(NavigationPanel);
    MainEditorPanel->setMaxComponent(SubEditorPanel);

    //Main Window Layout
    BorderLayoutRecPtr MainInternalWindowLayout = BorderLayout::create();

    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    MainEditorPanel->setConstraints(CenterConstraints);

    BorderLayoutConstraintsRecPtr NorthConstraints = BorderLayoutConstraints::create();
    NorthConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    ToolBarPanel->setConstraints(NorthConstraints);

    BorderLayoutConstraintsRecPtr SouthConstraints = BorderLayoutConstraints::create();
    SouthConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    StatusBarPanel->setConstraints(SouthConstraints);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ToolBarPanel);
    MainInternalWindow->pushToChildren(MainEditorPanel);
    MainInternalWindow->pushToChildren(StatusBarPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    MainInternalWindow->setBorders(NULL);
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);
    MainInternalWindow->setMenuBar(MainMenuBar);

    return InternalWindowTransitPtr(MainInternalWindow);
}

