s/upb_fielddef_options/upb_FieldDef_Options/g;
s/upb_fielddef_hasoptions/upb_FieldDef_HasOptions/g;
s/upb_fielddef_fullname/upb_FieldDef_FullName/g;
s/upb_fielddef_type/upb_FieldDef_CType/g;
s/upb_fielddef_descriptortype/upb_FieldDef_Type/g;
s/upb_fielddef_label/upb_FieldDef_Label/g;
s/upb_fielddef_number/upb_FieldDef_Number/g;
s/upb_fielddef_name/upb_FieldDef_Name/g;
s/upb_fielddef_jsonname/upb_FieldDef_JsonName/g;
s/upb_fielddef_hasjsonname/upb_FieldDef_HasJsonName/g;
s/upb_fielddef_isextension/upb_FieldDef_IsExtension/g;
s/upb_fielddef_packed/upb_FieldDef_IsPacked/g;
s/upb_fielddef_file/upb_FieldDef_File/g;
s/upb_fielddef_containingtype/upb_FieldDef_ContainingType/g;
s/upb_fielddef_extensionscope/upb_FieldDef_ExtensionScope/g;
s/upb_fielddef_containingoneof/upb_FieldDef_ContainingOneof/g;
s/upb_fielddef_realcontainingoneof/upb_FieldDef_RealContainingOneof/g;
s/upb_fielddef_index/upb_FieldDef_Index/g;
s/upb_fielddef_issubmsg/upb_FieldDef_IsSubMessage/g;
s/upb_fielddef_isstring/upb_FieldDef_IsString/g;
s/upb_fielddef_isseq/upb_FieldDef_IsRepeated/g;
s/upb_fielddef_isprimitive/upb_FieldDef_IsPrimitive/g;
s/upb_fielddef_ismap/upb_FieldDef_IsMap/g;
s/upb_fielddef_hasdefault/upb_FieldDef_HasDefault/g;
s/upb_fielddef_defaultint64/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultint32/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultuint64/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultuint32/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultbool/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultfloat/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultdouble/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_defaultstr/REPLACE_WITH_UPB_FIELDDEF_DEFAULT/g;
s/upb_fielddef_hassubdef/upb_FieldDef_HasSubDef/g;
s/upb_fielddef_haspresence/upb_FieldDef_HasPresence/g;
s/upb_fielddef_msgsubdef/upb_FieldDef_MessageSubDef/g;
s/upb_fielddef_enumsubdef/upb_FieldDef_EnumSubDef/g;
s/upb_fielddef_layout/upb_FieldDef_Layout/g;
s/_upb_fielddef_extlayout/_upb_FieldDef_ExtensionLayout/g;
s/_upb_fielddef_proto3optional/_upb_FieldDef_IsProto3Optional/g;
s/upb_fielddef_default/upb_FieldDef_Default/g;
s/upb_fielddef/upb_FieldDef/g;

s/upb_oneofdef_options/upb_OneofDef_Options/g;
s/upb_oneofdef_hasoptions/upb_OneofDef_HasOptions/g;
s/upb_oneofdef_name/upb_OneofDef_Name/g;
s/upb_oneofdef_containingtype/upb_OneofDef_ContainingType/g;
s/upb_oneofdef_index/upb_OneofDef_Index/g;
s/upb_oneofdef_issynthetic/upb_OneofDef_IsSynthetic/g;
s/upb_oneofdef_fieldcount/upb_OneofDef_FieldCount/g;
s/upb_oneofdef_field/upb_OneofDef_Field/g;
s/upb_oneofdef_ntofz/upb_OneofDef_LookupName/g;
s/upb_oneofdef_ntof/upb_OneofDef_LookupNameWithSize/g;
s/upb_oneofdef_itof/upb_OneofDef_LookupNumber/g;
s/upb_oneofdef/upb_OneofDef/g;

s/upb_msgdef_options/upb_MessageDef_Options/g;
s/upb_msgdef_hasoptions/upb_MessageDef_HasOptions/g;
s/upb_msgdef_fullname/upb_MessageDef_FullName/g;
s/upb_msgdef_file/upb_MessageDef_File/g;
s/upb_msgdef_containingtype/upb_MessageDef_ContainingType/g;
s/upb_msgdef_name/upb_MessageDef_Name/g;
s/upb_msgdef_syntax/upb_MessageDef_Syntax/g;
s/upb_msgdef_wellknowntype/upb_MessageDef_WellKnownType/g;
s/upb_msgdef_extrangecount/upb_MessageDef_ExtensionRangeCount/g;
s/upb_msgdef_fieldcount/upb_MessageDef_FieldCount/g;
s/upb_msgdef_oneofcount/upb_MessageDef_OneofCount/g;
s/upb_msgdef_extrange/upb_MessageDef_ExtensionRange/g;
s/upb_msgdef_field/upb_MessageDef_Field/g;
s/upb_msgdef_oneof/upb_MessageDef_Oneof/g;
s/upb_msgdef_ntooz/upb_MessageDef_FindOneofByName/g;
s/upb_msgdef_ntofz/upb_MessageDef_FindFieldByName/g;
s/upb_msgdef_itof/upb_MessageDef_FindFieldByNumberWithSize/g;
s/upb_msgdef_ntof/upb_MessageDef_FindFieldByNameWithSize/g;
s/upb_msgdef_ntoo/upb_MessageDef_FindOneofByNameWithSize/g;
s/upb_msgdef_layout/upb_MessageDef_Layout/g;
s/upb_msgdef_mapentry/upb_MessageDef_IsMapEntry/g;
s/upb_msgdef_nestedmsgcount/upb_MessageDef_NestedMessageCount/g;
s/upb_msgdef_nestedenumcount/upb_MessageDef_NestedEnumCount/g;
s/upb_msgdef_nestedextcount/upb_MessageDef_NestedExtensionCount/g;
s/upb_msgdef_nestedmsg/upb_MessageDef_NestedMessage/g;
s/upb_msgdef_nestedenum/upb_MessageDef_NestedEnum/g;
s/upb_msgdef_nestedext/upb_MessageDef_NestedExtension/g;
s/upb_msgdef_lookupnamez/upb_MessageDef_FindByName/g;
s/upb_msgdef_lookupname/upb_MessageDef_FindByNameWithSize/g;
s/upb_msgdef_lookupjsonnamez/upb_MessageDef_FindByNameName/g;
s/upb_msgdef_lookupjsonname/upb_MessageDef_FindByJsonNameWithSize/g;
s/upb_msgdef/upb_MessageDef/g;
s/WithSizez//g;

s/upb_extrange_options/upb_ExtensionRange_Options/g;
s/upb_extrange_hasoptions/upb_ExtensionRange_HasOptions/g;
s/upb_extrange_start/upb_ExtensionRange_Start/g;
s/upb_extrange_end/upb_ExtensionRange_End/g;
s/upb_extrange/upb_ExtensionRange/g;

s/upb_enumdef_options/upb_EnumDef_Options/g;
s/upb_enumdef_hasoptions/upb_EnumDef_HasOptions/g;
s/upb_enumdef_fullname/upb_EnumDef_FullName/g;
s/upb_enumdef_name/upb_EnumDef_Name/g;
s/upb_enumdef_file/upb_EnumDef_File/g;
s/upb_enumdef_containingtype/upb_EnumDef_ContainingType/g;
s/upb_enumdef_default/upb_EnumDef_Default/g;
s/upb_enumdef_valuecount/upb_EnumDef_ValueCount/g;
s/upb_enumdef_value/upb_EnumDef_Value/g;
s/upb_enumdef_lookupnamez/upb_EnumDef_FindValueByName/g;
s/upb_enumdef_lookupname/upb_EnumDef_FindValueByNameWithSize/g;
s/upb_enumdef_lookupnum/upb_EnumDef_FindValueByNumber/g;
s/upb_enumdef_checknum/upb_EnumDef_CheckNumber/g;
s/upb_enumdef/upb_EnumDef/g;

s/upb_enumvaldef_options/upb_EnumValueDef_Options/g;
s/upb_enumvaldef_hasoptions/upb_EnumValueDef_HasOptions/g;
s/upb_enumvaldef_fullname/upb_EnumValueDef_FullName/g;
s/upb_enumvaldef_name/upb_EnumValueDef_Name/g;
s/upb_enumvaldef_number/upb_EnumValueDef_Number/g;
s/upb_enumvaldef_index/upb_EnumValueDef_Index/g;
s/upb_enumvaldef_enum/upb_EnumValueDef_Enum/g;
s/upb_enumvaldef\b/upb_EnumValueDef/g;

s/upb_filedef_options/upb_FileDef_Options/g;
s/upb_filedef_hasoptions/upb_FileDef_HasOptions/g;
s/upb_filedef_name/upb_FileDef_Name/g;
s/upb_filedef_package/upb_FileDef_Package/g;
s/upb_filedef_syntax/upb_FileDef_Syntax/g;
s/upb_filedef_depcount/upb_FileDef_DependencyCount/g;
s/upb_filedef_publicdepcount/upb_FileDef_PublicDependencyCount/g;
s/upb_filedef_weakdepcount/upb_FileDef_WeakDependencyCount/g;
s/upb_filedef_toplvlmsgcount/upb_FileDef_TopLevelMessageCount/g;
s/upb_filedef_toplvlenumcount/upb_FileDef_TopLevelEnumCount/g;
s/upb_filedef_toplvlextcount/upb_FileDef_TopLevelExtensionCount/g;
s/upb_filedef_servicecount/upb_FileDef_ServiceCount/g;
s/upb_filedef_dep/upb_FileDef_Dependency/g;
s/upb_filedef_publicdep/upb_FileDef_PublicDependency/g;
s/upb_filedef_weakdep/upb_FileDef_WeakDependency/g;
s/upb_filedef_toplvlmsg/upb_FileDef_TopLevelMessage/g;
s/upb_filedef_toplvlenum/upb_FileDef_TopLevelEnum/g;
s/upb_filedef_toplvlext/upb_FileDef_TopLevelExtension/g;
s/upb_filedef_service/upb_FileDef_Service/g;
s/upb_filedef_symtab/upb_FileDef_Pool/g;
s/_upb_filedef_publicdepnums/_upb_FileDef_PublicDependencyNumbers/g;
s/_upb_filedef_weakdepnums/_upb_FileDef_WeakDependencyNumbers/g;
s/upb_filedef/upb_FileDef/g;

s/upb_methoddef_options/upb_MethodDef_Options/g;
s/upb_methoddef_hasoptions/upb_MethodDef_HasOptions/g;
s/upb_methoddef_fullname/upb_MethodDef_FullName/g;
s/upb_methoddef_name/upb_MethodDef_Name/g;
s/upb_methoddef_service/upb_MethodDef_Service/g;
s/upb_methoddef_inputtype/upb_MethodDef_InputType/g;
s/upb_methoddef_outputtype/upb_MethodDef_OutputType/g;
s/upb_methoddef_clientstreaming/upb_MethodDef_ClientStreaming/g;
s/upb_methoddef_serverstreaming/upb_MethodDef_ServerStreaming/g;
s/upb_methoddef/upb_MethodDef/g;

s/upb_servicedef_options/upb_ServiceDef_Options/g;
s/upb_servicedef_hasoptions/upb_ServiceDef_HasOptions/g;
s/upb_servicedef_fullname/upb_ServiceDef_FullName/g;
s/upb_servicedef_name/upb_ServiceDef_Name/g;
s/upb_servicedef_index/upb_ServiceDef_Index/g;
s/upb_servicedef_file/upb_ServiceDef_File/g;
s/upb_servicedef_methodcount/upb_ServiceDef_MethodCount/g;
s/upb_servicedef_method/upb_ServiceDef_Method/g;
s/upb_servicedef_lookupmethod/upb_ServiceDef_FindMethodByName/g;
s/upb_servicedef/upb_ServiceDef/g;

s/upb_symtab_new/upb_DefPool_New/g;
s/upb_symtab_free/upb_DefPool_Free/g;
s/upb_symtab_lookupmsg2/upb_DefPool_FindMessageByNameWithSize/g;
s/upb_symtab_lookupmsg/upb_DefPool_FindMessageByName/g;
s/upb_symtab_lookupenum/upb_DefPool_FindEnumByName/g;
s/upb_symtab_lookupenumval/upb_DefPool_FindEnumValueByName/g;
s/upb_symtab_lookupext2/upb_DefPool_FindExtensionByNameWithSize/g;
s/upb_symtab_lookupext/upb_DefPool_FindExtensionByName/g;
s/upb_symtab_lookupfile2/upb_DefPool_FindFileByNameWithSize/g;
s/upb_symtab_lookupfile/upb_DefPool_FindFileByName/g;
s/upb_symtab_lookupservice/upb_DefPool_FindServiceByName/g;
s/upb_symtab_lookupfileforsym/upb_DefPool_FindFileForSymbol/g;
s/upb_symtab_addfile/upb_DefPool_AddFile/g;
s/_upb_symtab_bytesloaded/_upb_DefPool_BytesLoaded/g;
s/_upb_symtab_arena/_upb_DefPool_Arena/g;
s/_upb_symtab_lookupextfield/_upb_DefPool_FindExtensionField/g;
s/upb_symtab_lookupextbynum/upb_DefPool_FindExtensionByNumber/g;
s/upb_symtab_extreg/upb_DefPool_ExtensionRegistry/g;
s/upb_symtab_getallexts/upb_DefPool_GetAllExtensions/g;
s/upb_symtab/upb_DefPool/g;

s/upb_def_init/_upb_DefPool_Init/g;

s/_upb_DefPool_loaddefinit/_upb_DefPool_LoadDefInit/g;

s/UPB_SYNTAX_PROTO2/kUpb_Syntax_Proto2/g;
s/UPB_SYNTAX_PROTO3/kUpb_Syntax_Proto3/g;
s/upb_syntax_t/upb_Syntax/g;

s/UPB_WELLKNOWN_UNSPECIFIED/kUpb_WellKnown_Unspecified/g;
s/UPB_WELLKNOWN_ANY/kUpb_WellKnown_Any/g;
s/UPB_WELLKNOWN_FIELDMASK/kUpb_WellKnown_FieldMask/g;
s/UPB_WELLKNOWN_DURATION/kUpb_WellKnown_Duration/g;
s/UPB_WELLKNOWN_TIMESTAMP/kUpb_WellKnown_Timestamp/g;
s/UPB_WELLKNOWN_DOUBLEVALUE/kUpb_WellKnown_DoubleValue/g;
s/UPB_WELLKNOWN_FLOATVALUE/kUpb_WellKnown_FloatValue/g;
s/UPB_WELLKNOWN_INT64VALUE/kUpb_WellKnown_Int64Value/g;
s/UPB_WELLKNOWN_UINT64VALUE/kUpb_WellKnown_UInt64Value/g;
s/UPB_WELLKNOWN_INT32VALUE/kUpb_WellKnown_Int32Value/g;
s/UPB_WELLKNOWN_UINT32VALUE/kUpb_WellKnown_UInt32Value/g;
s/UPB_WELLKNOWN_STRINGVALUE/kUpb_WellKnown_StringValue/g;
s/UPB_WELLKNOWN_BYTESVALUE/kUpb_WellKnown_BytesValue/g;
s/UPB_WELLKNOWN_BOOLVALUE/kUpb_WellKnown_BoolValue/g;
s/UPB_WELLKNOWN_VALUE/kUpb_WellKnown_Value/g;
s/UPB_WELLKNOWN_LISTVALUE/kUpb_WellKnown_ListValue/g;
s/UPB_WELLKNOWN_STRUCT/kUpb_WellKnown_Struct/g;
s/upb_wellknowntype_t/kUpb_WellKnown/g;

s/UPB_MAX_FIELDNUMBER/kUpb_MaxFieldNumber/g;

s/UPB_MAPENTRY_KEY/kUpb_MapEntry_KeyFieldNumber/g;
s/UPB_MAPENTRY_VALUE/kUpb_MapEntry_ValueFieldNumber/g;
s/UPB_ANY_TYPE/kUpb_Any_TypeFieldNumber/g;
s/UPB_ANY_VALUE/kUpb_Any_ValueFieldNumber/g;
s/UPB_DURATION_SECONDS/kUpb_Duration_SecondsFieldNumber/g;
s/UPB_DURATION_NANOS/kUpb_Duration_NanosFieldNumber/g;
s/UPB_TIMESTAMP_SECONDS/kUpb_Timestamp_SecondsFieldNumber/g;
s/UPB_TIMESTAMP_NANOS/kUpb_Timestamp_NanosFieldNumber/g;

s/upb_status_errmsg/upb_Status_ErrorMessage/g;
s/upb_ok/upb_Status_IsOk/g;
s/upb_status_clear/upb_Status_Clear/g;
s/upb_status_seterrmsg/upb_Status_SetErrorMessage/g;
s/upb_status_seterrf/upb_Status_SetErrorFormat/g;
s/upb_status_vseterrf/upb_Status_VSetErrorFormat/g;
s/upb_status_vappenderrf/upb_Status_VAppendErrorFormat/g;
s/upb_status/upb_Status/g;
s/UPB_STATUS_MAX_MESSAGE/_kUpb_Status_MaxMessage/g;

s/upb_strview_make/upb_StringView_FromStringAndSize/g;
s/upb_strview_makez/upb_StringView_FromCString/g;
s/upb_strview_eql/upb_StringView_IsEqual/g;
s/upb_strview/upb_StringView/g;

s/UPB_STRVIEW_INIT/UPB_STRINGVIEW_INIT/g;
s/UPB_STRVIEW_FORMAT/UPB_STRINGVIEW_FORMAT/g;
s/UPB_STRVIEW_ARGS/UPB_STRINGVIEW_ARGS/g;
