<?php

/**
 * @file
 * Definition of the 'stylizer' panel style.
 */

if (module_exists('bangpoundstyles')) {
  // Plugin definition
  $plugin = array(
    'title' => t('!&# style'),
    'weight' => -10,
    'description' => t('Allows choice of multiple existing stylizer styles'),

    'render pane' => 'bangpoundstyle_style_render_pane',
    'pane settings form' => 'bangpoundstyles_style_settings_form',
    'pane settings form submit' => 'bangpoundstyles_style_settings_submit',
    'defaults' => array(
      'classes' => array(),
      'title_classes' => array(),
      'content_classes' => array(),
      'attributes' => array(),
      'styles' => array(),
      'hook' => 'panels_naked_style_render_pane',
      'children' => FALSE,
    ),
  );
}

/**
 * Settings form callback.
 */
function bangpoundstyles_style_settings_form($style_settings) {

  $form['classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Classes'),
    '#default_value' => implode(' ', $style_settings['classes']),
  );
  $form['title_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Title classes'),
    '#default_value' => implode(' ', $style_settings['title_classes']),
  );
  $form['content_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Content classes'),
    '#default_value' => implode(' ', $style_settings['content_classes']),
    '#description' => t('This setting is inoperable unless <code>panels-pane.tpl.php</code> is overridden.'),
  );
  $form['attributes'] = array(
    '#type' => 'textarea',
    '#title' => t('Attributes'),
    '#default_value' => (!empty($style_settings['attributes'])) ? \Symfony\Component\Yaml\Yaml::dump($style_settings['attributes']) : '',
  );

  $options = array(
    'panels_naked_style_render_pane' => 'Naked',
    'panels_pane' => 'No style',
  );
  $hooks = theme_get_registry(FALSE);
  foreach (preg_grep('#^panels_pane__#i', array_keys(theme_get_registry())) as $hook) {
    $keys = explode('__', $hook);
    if (!empty($hooks[$hook]['bangpoundstyle'])) {
      $options[$hook] = $keys[1];
    }
  }
  $form['hook'] = array(
    '#type' => 'select',
    '#title' => t('Theme hook'),
    '#options' => $options,
    '#default_value' => (isset($style_settings['hook'])) ? $style_settings['hook'] : 'panels_naked_style_render_pane',
  );
  $form['children'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apply to children'),
    '#return_value' => TRUE,
    '#default_value' => (isset($style_settings['children'])) ? $style_settings['children'] : FALSE,
  );

  return $form;
}

function bangpoundstyles_style_settings_submit($form, &$settings, &$form_state) {
  foreach (array_keys($form_state['style']['defaults']) as $key) {
    if ('attributes' === $key) {
      $value = trim($settings[$key]);
      if (!empty($value)) {
        $settings[$key] = \Symfony\Component\Yaml\Yaml::parse($value);
      }
      else {
        $settings[$key] = array();
      }
    }
    else if (in_array($key, array('classes', 'title_classes', 'content_classes'))) {
      $value = trim($settings[$key]);
      if (!empty($value)) {
        $settings[$key] = array_filter(explode(' ', $value));
      }
      else {
        $settings[$key] = array();
      }
    }
  }
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundstyle_style_render_pane($vars) {
  $hook = isset($vars['settings']['hook']) ? $vars['settings']['hook'] : 'panels_naked_style_render_pane';
  return theme($hook, $vars);
}
