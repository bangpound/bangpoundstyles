<?php

/**
 * @file
 * Definition of the style base for a pre-styled pane.
 */

$plugin = array(
  'category' => t('Basic styles'),
  'title' => t('Styled pane'),
  'description' => t('A styled box. You may set a class attribute for the pane, title and content.'),
  'module' => 'panels',
  'type' => 'pane',

  'css' => NULL,
  'icon' => 'icon.png',

  'defaults' => array(
    'classes' => array('panel-pane'),
    'title_classes' => array('pane-title'),
    'content_classes' => array('pane-content'),
    'palette' => array(),
  ),
  'palette' => array(
  ),

  'settings form' => 'bangpoundpanels_styled_pane_style_settings',
  'settings form validate' => 'bangpoundpanels_styled_pane_style_settings_validate',
  'settings form submit' => 'bangpoundpanels_styled_pane_style_settings_submit',
);

function bangpoundpanels_styled_pane_style_settings(&$form, &$form_state) {
  $form['classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Classes'),
    '#default_value' => implode(' ', $form_state['settings']['classes']),
  );
  $form['title_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Title classes'),
    '#default_value' => implode(' ', $form_state['settings']['title_classes']),
  );
  $form['content_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Content classes'),
    '#default_value' => implode(' ', $form_state['settings']['content_classes']),
    '#description' => t('This setting is inoperable unless <code>panels-pane.tpl.php</code> is overridden.'),
  );
  $form['palette'] = array(
    '#type' => 'value',
    '#value' => array(),
  );
}

function bangpoundpanels_styled_pane_style_settings_validate(&$form, &$form_state) {
  foreach (array_keys($form_state['base_style_plugin']['defaults']) as $key) {
    if ($key != 'palette') {
      $value = trim($form_state['values'][$key]);
      if (!empty($value)) {
        $form_state['values'][$key] = array_filter(explode(' ', $value));
      }
      else {
        $form_state['values'][$key] = array();
      }
    }
  }
}

function bangpoundpanels_styled_pane_style_settings_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['base_style_plugin']['defaults']) as $key) {
    $form_state['settings'][$key] = $form_state['values'][$key];
  }
}
