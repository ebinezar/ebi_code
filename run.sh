echo ""
echo "Checking Apache Server Status"
echo "---------------------------"
if ps aux | grep -v grep | grep apache > /dev/null
then
    echo "Apache service running, everything is fine"
else
    echo "Apache is not running, Install apache service"
    exit
fi

echo ""
echo "Checking PHP Status"
echo "---------------------------"
INPUT=`php -v`
insv=`expr substr "$INPUT" 5 3`

st=$(echo "$insv >= 5.2" | bc)
if [ $st -eq 1 ]; then # 1 == true
  echo "Right version of PHP is Installed"
else
  echo "Installed PHP version is not ok, Please Upgrade"
  exit
fi

echo ""
echo "Checking the PHP dependency"
echo "---------------------------"
phpm=`php -m`
needgd=" gd "
needmmysqli=" mysqli "
if `echo ${phpm} | grep "${needgd}" 1>/dev/null 2>&1`
then
  echo ""
  echo "Checking GD Library Status - Success"
else
  echo "GD Library is not installed, Please install gd to proceed"
  exit
fi
	
if `echo ${phpm} | grep "${needmmysqli}" 1>/dev/null 2>&1`
then
  echo ""
  echo "Checking Mysqli Status - Success"
else
  echo "\n\n\nMysqli is not installed, Please install to proceed\n\n\n"
  exit
fi

echo ""
echo "Checking Mysql Server Status"
echo "---------------------------"
if ps ax | grep -v grep | grep mysqld > /dev/null
then
    echo "Mysql service is running, everything is fine"
else
    echo "Mysql is not running, please install Mysql"
    exit;	
fi



mysql -u root -e "" 2> /dev/null
if [ $? == 0 ]
then	
	mysql -u root -e "CREATE USER 'portal_user'@'localhost' IDENTIFIED BY 'p055w0rd'" 2> /dev/null
	mysql -u root -e "GRANT ALL PRIVILEGES ON *.* TO 'portal_user'@'localhost' WITH GRANT OPTION" 2> /dev/null
	mysqladmin -u root password p055w0rd
else
	mysql -u root -pp055w0rd -e "" 2> /dev/null
	if [ $? == 0 ]
	then	
		mysql -u root -pp055w0rd -e "CREATE USER 'portal_user'@'localhost' IDENTIFIED BY 'p055w0rd'" 2> /dev/null
		mysql -u root -pp055w0rd -e "GRANT ALL PRIVILEGES ON *.* TO 'portal_user'@'localhost' WITH GRANT OPTION" 2> /dev/null
	else
		echo ""
		echo "Creating Mysql user for Portal"
		echo "---------------------------"
		echo -n "Enter Mysql root Password: "
		stty -echo
		read password
		stty echo
		echo ""        
		mysql -u root -p$password -e "" 2> /dev/null
		if [ $? == 0 ]
		then	
			mysql -u root -p$password -e "CREATE USER 'portal_user'@'localhost' IDENTIFIED BY 'p055w0rd'" 2> /dev/null
			mysql -u root -p$password -e "GRANT ALL PRIVILEGES ON *.* TO 'portal_user'@'localhost' WITH GRANT OPTION" 2> /dev/null
		else 
			echo ""
			echo ""
			echo ""
			echo "--------------------You have entered wrong root password! Running the script again to request the correct password!--------------------"
			echo ""
			echo ""
			echo ""
			./run.sh
			exit 	
		fi
	fi
fi

self="${0#./}"
base="${self%/*}"
current=$(pwd)

if [ "$base" = "run.sh" ] ; then
result="$(pwd)"
else
result="$base"
fi ;

cd "$result"

echo ""
echo "installing Drupal"
echo "------------------"
chmod 777 -R sites/default/settings.php sites/default/files
sites/all/tools/drush/drush -y site-install6
echo ""
echo "installing Modules"
echo "------------------"
sites/all/tools/drush/drush -y pm-enable profile admin_menu backup_migrate imce imce_wysiwyg path token pathauto views views_ui views_export wysiwyg  developer_connect_settings developer_connect_user captcha image_captcha googleanalytics php node_export search mass_contact multiblock statistics author_pane advanced_blog drush_views tagadelic tagadelic_views taxonomy_export developer_connect_service_links developer_connect_search_type content content_copy content_permissions fieldgroup nodereference number optionwidgets text userreference developer_connect_node_settings developer_connect_api developer_connect_user_feedback_ext developer_connect_salt developer_connect_blog developer_connect_help securepages elysia_cron views_calc login_security adminrole  autologout user_feedback developer_connect_advanced_forum_ext faq developer_connect_faq_ext weight content_access admin_menu_toolbar
echo ""
echo "Modules are installed."
echo ""
echo "updating normal settings for Developer Connect Portal"
echo "-----------------------------------------------------"
sites/all/tools/drush/drush theme-set-default aloha
sites/all/tools/drush/drush views-import
sites/all/tools/drush/drush cck_import-import < export/cck/api.content
sites/all/tools/drush/drush cck_import-import < export/cck/api_method.content
sites/all/tools/drush/drush cck_import-import < export/cck/class_name.content
sites/all/tools/drush/drush vset --yes pathauto_node_pattern "[type]/[title-raw]";
sites/all/tools/drush/drush node_export-import < export/nodes/export_file.node
sites/all/tools/drush/drush node_export-import < export/nodes/export_faqnode.node
sites/all/tools/drush/drush sql-import < export/queries/taxonomy_import.sql
sites/all/tools/drush/drush block-cache-clear
sites/all/tools/drush/drush sql-import < export/queries/queries.sql
sites/all/tools/drush/drush --y search-index
sites/all/tools/drush/drush cc all
mkdir sites/default/files/pictures
mkdir sites/default/files/report_bugs
chmod -R 777 sites/default/files
sites/all/tools/drush/drush php-eval 'node_access_rebuild();';
echo ""
echo "SUCCESSFULLY INSTALLED."
echo "\$GLOBALS['sdm_version'] = 'generic 3.8.2';" >> sites/default/settings.php
