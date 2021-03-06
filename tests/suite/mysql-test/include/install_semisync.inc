#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
--let $include_filename= install_semisync.inc
--source include/begin_include_file.inc

--source include/not_embedded.inc
--source include/have_semisync_plugin.inc


--disable_query_log
--let $value = query_get_value(show variables like 'rpl_semi_sync_master_enabled', Value, 1)
if ($value == No such row)
{
    SET sql_log_bin = 0;
    eval INSTALL PLUGIN rpl_semi_sync_master SONAME '$SEMISYNC_MASTER_PLUGIN';
    SET sql_log_bin = 1;
}
--enable_query_log

--source include/stop_slave_io.inc

--disable_query_log
--let $value= query_get_value(show variables like 'rpl_semi_sync_slave_enabled', Value, 1)
if ($value == No such row)
{
    SET sql_log_bin = 0;
    eval INSTALL PLUGIN rpl_semi_sync_slave SONAME '$SEMISYNC_SLAVE_PLUGIN';
    SET sql_log_bin = 1;
}
--source include/start_slave_io.inc
--enable_query_log

--source include/end_include_file.inc
