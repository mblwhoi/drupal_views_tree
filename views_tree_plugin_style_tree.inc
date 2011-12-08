<?php

/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item in a slideshow of an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class views_tree_plugin_style_tree extends views_plugin_style_list {

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['main_field'] = array('default' => '');
    $options['parent_field'] = array('default' => '');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    watchdog(WATCHDOG_DEBUG, __FILE .': '. __LINE__);
    $fields = array('' => t('<None>'));

    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      if ($label = $handler->label()) {
        $fields[$field] = $label;
      }
      else {
        $fields[$field] = $handler->ui_name();
      }
    }

    $events = array('click' => t('On Click'), 'mouseover' => t('On Mouseover'));

    $form['type']['#description'] = t('Whether to use an ordered or unordered list for the retrieved items. Most use cases will prefer Unordered.');
    
    if (empty($this->options['collapsible_label'])) {
      $this->options['collapsible_label'] = t('Children: ([children_count])');
    }

    $form['main_field'] = array(
      '#type' => 'select',
      '#title' => t('Main field'),
      '#options' => $fields,
      '#default_value' => $this->options['main_field'],
      '#description' => t('Select the field with the unique identifier for each record.'),
      '#required' => TRUE,
    );

    $form['parent_field'] = array(
      '#type' => 'select',
      '#title' => t('Parent field'),
      '#options' => $fields,
      '#default_value' => $this->options['parent_field'],
      '#description' => t('Select the field that contains the unique identifier of the record\'s parent.'),
    );
    
    $form['collapsible_tree'] = array(
      '#type' => 'radios',
      '#title' => t('Collapsible view'),
      '#default_value' => $this->options['collapsible_tree'],
      '#options' => array(
        0 => t('Off'),
        'all' => t('Collapse everything'),
        'part' => t('Collapse children only'),
      ),
    );

    $form['collapsible_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label for collapsible control'),
      '#default_value' => $this->options['collapsible_label'],
      '#description' => t('Label to display on the collapsible control.  May contain replacements <i>[fieldname]</i> for any field in the view, or [children_count].'),
      '#size' => 70,
      '#maxlength' => 250,
    );
  }
}
