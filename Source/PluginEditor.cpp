/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
ZmidiAudioProcessorEditor::ZmidiAudioProcessorEditor (ZmidiAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (420, 160);
    // Look and Feel
    //bg = juce::Colour(57, 61, 63);
    bg = juce::Colour(33,33,33);
    bg2 = juce::Colour(35, 45, 50);
    c1 = juce::Colour(0, 168, 150);
    c2 = juce::Colour(2, 195, 154);
    c3 = juce::Colour(242, 27, 63);
    c4 = juce::Colour(240, 243, 189);
    juce::StringArray AvailableFonts = juce::Font::findAllTypefaceNames();
    if (AvailableFonts.contains("Tahoma")) {
        getLookAndFeel().setDefaultSansSerifTypefaceName("Tahoma");
    }
    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, c2);
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, bg);
    getLookAndFeel().setColour(juce::Slider::textBoxBackgroundColourId, bg2);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, c2);
    getLookAndFeel().setColour(juce::Slider::trackColourId, c2);
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, bg2);
    getLookAndFeel().setColour(juce::ComboBox::textColourId, c2);
    getLookAndFeel().setColour(juce::ComboBox::arrowColourId, c2);
    getLookAndFeel().setColour(juce::ComboBox::outlineColourId, bg);
    getLookAndFeel().setColour(juce::ComboBox::buttonColourId, c2);
    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, bg2);
    getLookAndFeel().setColour(juce::PopupMenu::textColourId, c1);
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, c1);
    getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, c4);
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, bg2);
    getLookAndFeel().setColour(juce::TextButton::textColourOffId, c2);
    getLookAndFeel().setColour(juce::AlertWindow::backgroundColourId, bg);
    getLookAndFeel().setColour(juce::AlertWindow::textColourId, c4);
    //slider1.setTransform(juce::AffineTransform::rotation(-0.05));
    //slider2.setTransform(juce::AffineTransform::rotation(-0.05));
    // Type Selection
    addAndMakeVisible(typeSelect);
    typeSelect.addItem("Velocity Gain", 1);
    typeSelect.addItem("Absolute Velocity", 2);
    typeSelect.addItem("Min/Max Velocity", 3);
    typeSelect.onChange = [this] { typeSelectChanged(); };
    typeSelect.setSelectedId(audioProcessor.selectedType);
    typeSelect.setSize(420, 30);
    //

    // Sliders
    slider1.setRange(-127, 127, 1);
    slider2.setRange(1, 127, 1);
    slider1.setValue(audioProcessor.p1->get());
    slider2.setValue(audioProcessor.p2->get());
    // this function adds the sliders to the editor
    addAndMakeVisible(&slider1);
    addAndMakeVisible(&slider2);
    slider2.setVisible(false);
    slider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    slider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    slider1.addListener(this);
    slider2.addListener(this);
    // add the listener to the sliders
    audioProcessor.p1->addListener(this);
    //slider2.addListener(this);
    //slider1.onChange = [this] { paramChanged(); };
    //slider2.onChange = [this] { paramChanged(); };

    audioProcessor.p2->addListener(this); 

    //
    audioProcessor.cb.addChangeListener(this);

    //
    addAndMakeVisible(infoBtn);
    infoBtn.setButtonText("INFO");
    infoBtn.addListener(this);
}

ZmidiAudioProcessorEditor::~ZmidiAudioProcessorEditor()
{
    audioProcessor.cb.removeChangeListener(this);
    audioProcessor.p1->removeListener(this);
    audioProcessor.p2->removeListener(this);
}

//==============================================================================
void ZmidiAudioProcessorEditor::paint(juce::Graphics& g)
{
    // fill the whole window
    g.fillAll(bg);
    // set the current drawing colour
    
    // set the font size and draw text to the screen
    //g.setFont(32.0f);
    //g.drawFittedText(title, 0, 40, getWidth(), 20, juce::Justification::centred, 1);
    
    /*g.setColour(bg2);
    juce::Path path;
    float w = getWidth();
    float h = getHeight();
    path.startNewSubPath(juce::Point<float>(w, h));
    path.lineTo(juce::Point<float>(w - 95.0f, h));
    path.lineTo(juce::Point<float>(w - 60.0f, h - 60.0f));
    path.lineTo(juce::Point<float>(w, h - 70.0f));
    path.closeSubPath();
    g.fillPath(path);*/
    if (audioProcessor.notesOn>0) {
        g.setColour(c3);
    }
    else {
        g.setColour(bg2);
    }
    juce::Path path;
    float w = getWidth();
    float h = getHeight();
    path.startNewSubPath(juce::Point<float>(w-75.0f, h-20.0f));
    path.lineTo(juce::Point<float>(w-85.0f,h-30.0f));
    path.lineTo(juce::Point<float>(w-75.0f, h-40.0f));
    path.lineTo(juce::Point<float>(w-65.0f, h-30.0f));
    path.closeSubPath();
    g.fillPath(path);

    
    /*g.setColour(c3);
    g.setOpacity(0.5);
    juce::Line<float> line(juce::Point<float>(0, 25),
        juce::Point<float>(getWidth()-80, 25));
    g.drawLine(line, 5.0f);

    g.setColour(c2);
    g.setOpacity(0.5);
    juce::Line<float> line2(juce::Point<float>(0, 30),
        juce::Point<float>(getWidth() - 120, 30));
    g.drawLine(line2, 5.0f);*/

    g.setColour(c3);
    g.fillRect(getWidth()-20, getHeight() - 42, getWidth() / 2, 3);
    g.setColour(c2);
    g.fillRect(getWidth()-20, getHeight() - 22, getWidth() / 2, 3);

    g.setFont(16.0f);

    g.setColour(c3);
    juce::String inVel = std::to_string(audioProcessor.noteInVel);
    //inVel = inVel.substring(0, inVel.indexOfChar('.'));
    g.drawFittedText(inVel + " <", -20, getHeight() - 50, getWidth(), 20, juce::Justification::right, 1);
    
    g.setColour(c2);
    juce::String outVel = std::to_string(audioProcessor.noteOutVel);
    //outVel = outVel.substring(0, outVel.indexOfChar('.'));
    g.drawFittedText(outVel + " >", -20, getHeight() - 30, getWidth(), 20, juce::Justification::right, 1);
    
    //repaint();// Always be painting
    
}

void ZmidiAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
    slider1.setBounds(40, 50, 340, 60);
    slider2.setBounds(210, 50, 170, 60);
    typeSelect.setBounds(0,0,getWidth(), 30);

    infoBtn.setBounds(10, getHeight()-30, 40,20);
}

void ZmidiAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    /*audioProcessor.noteModVel = slider1.getValue();*/
    audioProcessor.p1->operator= (slider1.getValue());
    audioProcessor.p2->operator= (slider2.getValue());
    /*if (typeSelect.getSelectedId() == 3) {
        audioProcessor.min = slider1.getValue();
        audioProcessor.max = slider2.getValue();
    }*/
    repaint();
}

void ZmidiAudioProcessorEditor::typeSelectChanged()
{
    audioProcessor.selectedType = typeSelect.getSelectedId();
    switch (typeSelect.getSelectedId())
    {
        case 1: 
            showOneSlider();
            //title = "VELOCITY GAIN";
            slider1.setRange(-127.0, 127.0, 1.0);
            //slider1.setValue(0.0);
            break;
        case 2: 
            showOneSlider();
            floorVelocity();
            //title = "ABSOLUTE VELOCITY"; 
            slider1.setRange(0.0, 127.0, 1.0);
            break;
        case 3:
            showTwoSliders();
            floorVelocity();
            //title = "MIN/MAX VELOCITY";
            slider1.setRange(0.0, 127.0, 1.0);
            break;
        //case 3: textFont.setStyleFlags(juce::Font::italic); break;
        default: break;
    }
    repaint();
}

void ZmidiAudioProcessorEditor::showOneSlider()
{
    slider1.setBounds(40, 50, 340, 60);
    slider2.setVisible(false);
}
void ZmidiAudioProcessorEditor::showTwoSliders()
{
    slider1.setBounds(40, 50, 170, 60);
    slider2.setVisible(true);
}

void ZmidiAudioProcessorEditor::parameterValueChanged(int 	parameterIndex,
    float 	newValue
)
{
    slider1.setValue(audioProcessor.p1->get());
    slider2.setValue(audioProcessor.p2->get());
    if (typeSelect.getSelectedId() == 3) {//min/max
        // Ensure that max is always at least min
        if (audioProcessor.p1->get() > audioProcessor.p2->get()) {
            audioProcessor.p2->operator= (audioProcessor.p1->get());
        }
    }
}
void ZmidiAudioProcessorEditor::parameterGestureChanged(int 	parameterIndex,
    bool 	gestureIsStarting
) {
    
}

void ZmidiAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}
void ZmidiAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    //juce::AlertWindow("title", "message", juce::MessageBoxIconType::InfoIcon);
    juce::String project = ProjectInfo::projectName;
    juce::String company = ProjectInfo::companyName;
    juce::String version = ProjectInfo::versionString;
    juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::NoIcon, project, version+"\r\n\r\n\r\n"+company+"\r\nMathieu Dombrock 2022", "yeet");
}
void ZmidiAudioProcessorEditor::floorVelocity()
{
    if (audioProcessor.p1->get() < 0) {
        audioProcessor.p1->operator= (0);
    }
    if (audioProcessor.p2->get() < 0) {
        audioProcessor.p2->operator= (0);
    }
}
