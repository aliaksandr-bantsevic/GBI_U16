object Form_SystemAdjust: TForm_SystemAdjust
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1089#1080#1089#1090#1077#1084#1099
  ClientHeight = 362
  ClientWidth = 785
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 18
  object Button_exit: TButton
    Left = 662
    Top = 329
    Width = 115
    Height = 25
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 0
    OnClick = Button_exitClick
  end
  object Button1: TButton
    Left = 543
    Top = 329
    Width = 113
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 1
    OnClick = Button1Click
  end
  object PageControl_system_adjust: TPageControl
    Left = 0
    Top = 2
    Width = 785
    Height = 321
    ActivePage = TabSheet_system_adjust_common
    TabOrder = 2
    TabStop = False
    object TabSheet_system_adjust_common: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      object Label1: TLabel
        Left = 13
        Top = 14
        Width = 103
        Height = 18
        Caption = #1048#1084#1103' '#1089#1080#1089#1090#1077#1084#1099
      end
      object Label6: TLabel
        Left = 13
        Top = 54
        Width = 327
        Height = 18
        Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1077' '#1095#1080#1089#1083#1086' '#1079#1072#1087#1080#1089#1077#1081' '#1074' '#1080#1079#1084#1077#1088#1077#1085#1080#1080
      end
      object Label7: TLabel
        Left = 13
        Top = 99
        Width = 326
        Height = 18
        Caption = #1063#1080#1089#1083#1086' '#1079#1072#1087#1080#1089#1077#1081' '#1074' '#1080#1079#1084#1077#1088#1077#1085#1080#1080' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
      end
      object Label8: TLabel
        Left = 13
        Top = 136
        Width = 357
        Height = 18
        Caption = #1047#1072#1087#1088#1072#1096#1080#1074#1072#1090#1100' '#1087#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1077' '#1087#1088#1080' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1080
        Visible = False
      end
      object Edit_name: TEdit
        Left = 391
        Top = 11
        Width = 368
        Height = 26
        TabOrder = 0
      end
      object ComboBox_records_max: TComboBox
        Left = 391
        Top = 51
        Width = 160
        Height = 26
        Enabled = False
        TabOrder = 1
      end
      object ComboBox_records_default: TComboBox
        Left = 391
        Top = 96
        Width = 160
        Height = 26
        TabOrder = 2
      end
      object CheckBox_ask_param_apply: TCheckBox
        Left = 391
        Top = 137
        Width = 97
        Height = 17
        TabOrder = 3
        Visible = False
      end
    end
    object TabSheet_backup: TTabSheet
      Caption = #1056#1077#1079#1077#1088#1074#1085#1086#1077' '#1082#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077
      ImageIndex = 1
      object Label9: TLabel
        Left = 55
        Top = 27
        Width = 272
        Height = 18
        Caption = 'C'#1086#1093#1088#1072#1085#1077#1085#1103#1090#1100' '#1082#1086#1087#1080#1102' '#1041#1044' '#1089' '#1087#1077#1088#1080#1086#1076#1086#1084
      end
      object Label10: TLabel
        Left = 539
        Top = 27
        Width = 38
        Height = 18
        Caption = #1076#1085#1077#1081
      end
      object ComboBox_backup: TComboBox
        Left = 352
        Top = 24
        Width = 145
        Height = 26
        TabOrder = 0
        Text = '1'
      end
      object CheckBox_backup: TCheckBox
        Left = 24
        Top = 28
        Width = 25
        Height = 17
        TabOrder = 1
        OnClick = CheckBox_backupClick
      end
    end
    object TabSheet_timers: TTabSheet
      Caption = #1058#1072#1081#1084#1077#1088#1099
      ImageIndex = 2
      TabVisible = False
      object Label2: TLabel
        Left = 13
        Top = 46
        Width = 184
        Height = 18
        Caption = #1055#1077#1088#1080#1086#1076' '#1086#1087#1088#1086#1089#1072' '#1076#1072#1090#1095#1080#1082#1072
      end
      object Label3: TLabel
        Left = 13
        Top = 78
        Width = 145
        Height = 18
        Caption = #1058#1072#1081#1084#1072#1091#1090' '#1085#1072' '#1095#1090#1077#1085#1080#1077
      end
      object Label4: TLabel
        Left = 13
        Top = 110
        Width = 143
        Height = 18
        Caption = #1058#1072#1081#1084#1072#1091#1090' '#1085#1072' '#1079#1072#1087#1080#1089#1100
      end
      object Label5: TLabel
        Left = 13
        Top = 142
        Width = 275
        Height = 18
        Caption = #1047#1072#1076#1077#1088#1078#1082#1072' '#1085#1072' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1077' '#1082#1086#1084#1072#1085#1076#1099
      end
      object ComboBox_ask_sensor_period: TComboBox
        Left = 391
        Top = 43
        Width = 160
        Height = 26
        TabOrder = 0
      end
      object ComboBox_tout_read: TComboBox
        Left = 391
        Top = 75
        Width = 160
        Height = 26
        TabOrder = 1
      end
      object ComboBox_tout_write: TComboBox
        Left = 391
        Top = 107
        Width = 160
        Height = 26
        TabOrder = 2
      end
      object ComboBox_cmd_delay: TComboBox
        Left = 391
        Top = 139
        Width = 160
        Height = 26
        TabOrder = 3
      end
    end
  end
  object Timer_start: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer_startTimer
    Left = 8
    Top = 328
  end
end
