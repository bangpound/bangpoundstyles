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
    'defaults' => array(
      'styles' => array(),
      'hook' => 'panels_naked_style_render_pane',
      'children' => FALSE,
    ),

  //  'settings validate' => 'bangpoundstyles_style_settings_validate',
  );
}

/**
 * Settings form callback.
 */
function bangpoundstyles_style_settings_form($style_settings) {
  $styles = bangpoundstyles_get_stylizer_styles();
  $options = array();
  foreach ($styles as $name => $style) {
    $options[$name] = $style->admin_title;
  }
  $form['styles'] = array(
    '#title' => t('Styles'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => (isset($style_settings['styles'])) ? $style_settings['styles'] : array(),
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

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundstyle_style_render_pane($vars) {
  $hook = isset($vars['settings']['hook']) ? $vars['settings']['hook'] : 'panels_naked_style_render_pane';
  return theme($hook, $vars);
}
