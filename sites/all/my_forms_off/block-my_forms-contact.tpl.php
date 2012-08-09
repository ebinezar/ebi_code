<?php 
global $base_url;
?>
<?php
$form['#attributes']['class'] = 'contact-forms';
 $form['#id'] = 'contact-block-form';
$output = '<div id="contact-form">';
 
$output .= drupal_render($form['check1']);
$output .= drupal_render($form['check2']);
$output .= drupal_render($form['check3']);
$output .= drupal_render($form['check4']);
$output .= drupal_render($form['check5']);
$output .= drupal_render($form['check6']);
$output .= drupal_render($form['check7']);
$output .= drupal_render($form['check8']);
$output .= drupal_render($form['check9']);
$output .= drupal_render($form['check10']);
$output .= drupal_render($form['check11']);
$output .= drupal_render($form['check12']);
$output .= drupal_render($form['submit']);
$output .= drupal_render($form['reset']);
$output .= '</div>';

print $output;

?>
