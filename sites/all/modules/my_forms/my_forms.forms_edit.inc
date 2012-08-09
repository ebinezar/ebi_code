<?php 
function forms_edit()
	{
	$lin = arg(2);
		
	$query = db_select('registration','r');

    	$query->fields('r',array('uid', 'name', 'Age','Sex','email','phone','region','addrlin1','new','prayer','film','door'))
   	->condition('uid', $lin);
        $result = $query->execute();

	while($node = $result->fetchAssoc()) 
	{
        $rows1 = $node['uid'] ? $node['uid'] :'N/A';
  	$rows2 = $node ['name'] ? $node ['name'] :'N/A';
	$rows3 = $node['age'] ? $node['age'] :'N/A';
	$rows4 = $node['sex'] ? $node['sex'] :'N/A';
  	$rows5 = $node['email'] ? $node['email'] :'N/A';
  	$rows6 = $node['phone'] ? $node['phone'] :'N/A';
	$rows7 = $node['region'] ? $node['region'] :'N/A';
	$rows8 = $node['addrlin1'] ? $node['addrlin1'] :'N/A';
	//$rows9 = $node['addrlin2'] ? $node['addrlin2'] :'N/A';
	$rows10 = $node['new'];
	$rows11 = $node['prayer'];
	$rows12 = $node['film'];
	$rows13 = $node['door'];
	}
	if($rows4 == 'male')
	$rows4 = 1; else $rows4 = 2;	//print_r($rows7);die;
	
	if($rows7 == 'T1')
	$rows7=0;
	if($rows7 == 'T2')
	$rows7=1;
	if($rows7 == 'T3')
	$rows7=2;
	if($rows7 == 'T4')
	$rows7=3;
	if($rows7 == 'T5')
	$rows7=4;
	if($rows7 == 'T6')
	$rows7=5;
	if($rows7 == 'T7')
	$rows7=6;
	if($rows7 == 'T8')
	$rows7=7;
	if($rows7 == 'T9')
	$rows7=8;
	if($rows7 == 'T10')
	$rows7=9;
	
	if($rows10  == "Yes")
	$check1 =  1; 
	if($rows11 == "Yes")
	$check2 = 2;
	if($rows12 == "Yes")
	$check3 =  3;
	if($rows13 == "Yes")
	$check4 =  4;//array(3 => 3);	
	
		
$form['name'] = array(
				'#type' => 'textfield',
				'#title' => t('Name:'),
				'#required' => TRUE,
				'#default_value' => $rows2,
				'#length' => 64,
				'#size' => 20,
				);
$form['age'] = array(
				'#type' => 'textfield',
				'#title' => t('Age:'),
				'#default_value' => $rows3,
				'#length' => 64,
				'#size' => 5,
				);
$form['sex'] = array(
				'#type' => 'radios',
				'#title' => t('Sex:'),
				'#default_value' => $rows4,
				'#options' => array(1 => 'male',2 => 'female'),
				
				);
								
$form['email'] = array(
				'#type' => 'textfield',
				'#title' => t('Email ID:'),
				'#rules' => array('email','length[10,20]'),
				'#default_value' => $rows5,
				'#length' => 64,
				'#size' => 20,
				);
$form['phone'] = array(
				'#type' => 'textfield',
				'#title' => t('Phone No:'),
				'#default_value' => $rows6,
				'#length' => 64,
				'#size' => 20,
				);
$form['region'] = array(
				'#type' => 'select',
				'#title' => t('Select the preffered Region'),
				'#required' => TRUE,
				'#default_value' => $rows7,				
				'#options' => array(		0 => 'T1',
								1 => 'T2',
								2 => 'T3',
								3 => 'T4',
								4 => 'T5',
								5 => 'T6',6 => 'T7',7 => 'T8',8 => 'T9',9 => 'T10',),
				);
$form['addrlin1'] = array(
				'#type' => 'textfield',
				'#title' => t('Address:'),
				'#required' => TRUE,
				'#default_value' => $rows8,				
				'#length' => 64,
				'#size' => 25,
				
				);

$form['check'] = array(
				'#type' => 'checkboxes',
				'#title' => t('Select preffered options'),
				'#default_value' => array(
								1 => $check1,
								2 => $check2,
								3 => $check3,
								4 => $check4),
				
				'#options' => array(
								1 => 'New comer',
								2 => 'Prayer booth',
								3 => 'Film show',
								4 => 'Door to door'),
				
				);
$form['submit'] = array(
		    '#type' => 'submit',
    		    '#value' => t('Update'),
		    //'#submit' => array('forms_edit_sub'),
			);
$form['cancel'] = array(
  		'#type' => 'submit',
  		'#value' => t('Cancel'),
 		'#submit' => array('form_cancel'),
		);
		return $form;
	}

function forms_edit_submit($form_id,$form_state)
{
	$lin=arg(2);
	if($form_state['values']['sex'] == 1)//radio button
	$sex="male";
	else $sex="female";
	//checkbox
	if($form_state['values']['check'][1] == 1)
	{ 
	$value1="Yes";
	}else $value1="N/A";
	if($form_state['values']['check'][2] == 2)
	{
	$value2 ="Yes";
	}else $value2="N/A";
	if($form_state['values']['check'][3] == 3)
	{
	$value3 ="Yes";
	}else $value3="N/A";
	if($form_state['values']['check'][4] == 4)
	{
	$value4 ="Yes";}
	else $value4="N/A";	//region
	if($form_state['values']['region'] == 0)
	$value="T1";
	if($form_state['values']['region'] == 1)
	$value="T2";
	if($form_state['values']['region'] == 2)
	$value="T3";
	if($form_state['values']['region'] == 3)
	$value="T4";
	if($form_state['values']['region'] == 4)
	$value="T5";
	if($form_state['values']['region'] == 5)
	$value="T6";
	if($form_state['values']['region'] == 6)
	$value="T7";
	if($form_state['values']['region'] == 7)
	$value="T8";
	if($form_state['values']['region'] == 8)
	$value="T9";
	if($form_state['values']['region'] == 9)
	$value="T10";
	
	 $update = db_update('registration')
	->fields(array(
    	//'uid' => $,
    	'name' => $form_state['values']['name'],
    	'Age' => $form_state['values']['age'] ,
	'Sex' => $sex,
	'email' => $form_state['values']['email'],
	'phone' => $form_state['values']['phone'],
	'region' => $value,
	'addrlin1' => $form_state['values']['addrlin1'],
	//'addrlin2' => $form_state['values']['addrlin2'],
	'new' => $value1,
	'prayer' => $value2,
	'film' => $value3,
	'door' => $value4,  ))
   -> condition('uid',$lin)
   -> execute();
   drupal_set_message(t('The form submitted successfully'));
	 drupal_goto('views');
	}

function form_cancel()
{
return drupal_goto('views');
}
