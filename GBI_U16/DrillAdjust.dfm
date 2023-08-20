object Form_DrillAdjust: TForm_DrillAdjust
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1082#1074#1072#1078#1080#1085#1091
  ClientHeight = 346
  ClientWidth = 868
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OnCreate = FormCreate
  TextHeight = 18
  object Label1: TLabel
    Left = 24
    Top = 27
    Width = 161
    Height = 18
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1089#1082#1074#1072#1078#1080#1085#1099':'
  end
  object Label2: TLabel
    Left = 24
    Top = 59
    Width = 114
    Height = 18
    Caption = #1063#1080#1089#1083#1086' '#1091#1088#1086#1074#1085#1077#1081
  end
  object Label_asimut: TLabel
    Left = 24
    Top = 127
    Width = 56
    Height = 18
    Caption = #1040#1079#1080#1084#1091#1090
  end
  object Label4: TLabel
    Left = 24
    Top = 91
    Width = 94
    Height = 18
    Caption = #1054#1088#1080#1077#1085#1090#1072#1094#1080#1103
  end
  object Button_cancel: TButton
    Left = 722
    Top = 313
    Width = 138
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 0
    OnClick = Button_cancelClick
  end
  object Button_apply: TButton
    Left = 586
    Top = 313
    Width = 129
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 1
    OnClick = Button_applyClick
  end
  object Edit_name: TEdit
    Left = 208
    Top = 24
    Width = 648
    Height = 26
    TabOrder = 2
    Text = #1057#1082#1074#1072#1078#1080#1085#1072
  end
  object ComboBox_meas_cnt: TComboBox
    Left = 208
    Top = 56
    Width = 176
    Height = 26
    TabOrder = 3
  end
  object Edit_asimut: TEdit
    Left = 208
    Top = 124
    Width = 176
    Height = 26
    TabOrder = 4
    Text = '0'
  end
  object ComboBox_orient: TComboBox
    Left = 208
    Top = 88
    Width = 176
    Height = 26
    TabOrder = 5
    Text = #1043#1086#1088#1080#1079#1086#1085#1090#1072#1083#1100#1085#1072#1103
    OnChange = ComboBox_orientChange
  end
  object CheckBox_single: TCheckBox
    Left = 401
    Top = 92
    Width = 129
    Height = 17
    Caption = #1054#1076#1080#1085'  '#1087#1088#1086#1093#1086#1076
    TabOrder = 6
  end
  object Edit_zshift: TEdit
    Left = 401
    Top = 147
    Width = 176
    Height = 26
    TabOrder = 7
    Visible = False
  end
  object RadioGroup1: TRadioGroup
    Left = 390
    Top = 51
    Width = 225
    Height = 122
    Caption = #1056#1072#1089#1095#1077#1090
    TabOrder = 8
  end
  object RadioButton_top: TRadioButton
    Left = 424
    Top = 92
    Width = 169
    Height = 17
    Caption = #1086#1090' '#1042#1045#1056#1061#1053#1045#1049' '#1090#1086#1095#1082#1080
    TabOrder = 9
  end
  object RadioButton_bot: TRadioButton
    Left = 424
    Top = 128
    Width = 169
    Height = 17
    Caption = #1086#1090' '#1053#1048#1046#1053#1045#1049' '#1090#1086#1095#1082#1080
    TabOrder = 10
  end
  object GroupBox_start_collect_data: TGroupBox
    Left = 634
    Top = 51
    Width = 225
    Height = 122
    Caption = #1057#1073#1086#1088' '#1076#1072#1085#1085#1099#1093
    TabOrder = 11
    object RadioButton_start_first: TRadioButton
      Left = 16
      Top = 36
      Width = 193
      Height = 17
      Caption = #1053#1072#1095#1080#1085#1072#1090#1100' '#1089' '#1087#1077#1088#1074#1086#1075#1086
      TabOrder = 0
    end
    object RadioButton_start_last: TRadioButton
      Left = 16
      Top = 72
      Width = 206
      Height = 17
      Caption = #1053#1072#1095#1080#1085#1072#1090#1100' '#1089' '#1087#1086#1089#1083#1077#1076#1085#1077#1075#1086
      TabOrder = 1
    end
  end
  object GroupBox2: TGroupBox
    Left = 392
    Top = 179
    Width = 468
    Height = 128
    Caption = #1043#1077#1086#1076#1077#1079#1080#1095#1077#1089#1082#1072#1103' '#1087#1088#1080#1074#1103#1079#1082#1072
    TabOrder = 12
    object Label3: TLabel
      Left = 16
      Top = 96
      Width = 96
      Height = 18
      Caption = #1058#1086#1095#1082#1072' '#1074#1093#1086#1076#1072
    end
    object Label5: TLabel
      Left = 264
      Top = 96
      Width = 109
      Height = 18
      Caption = #1058#1086#1095#1082#1072' '#1074#1099#1093#1086#1076#1072
    end
    object CheckBox_GeoOn: TCheckBox
      Left = 16
      Top = 24
      Width = 97
      Height = 17
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100
      TabOrder = 0
    end
    object Edit_Input_point: TEdit
      Left = 16
      Top = 64
      Width = 201
      Height = 26
      TabOrder = 1
    end
    object Edit_Output_point: TEdit
      Left = 256
      Top = 64
      Width = 201
      Height = 26
      TabOrder = 2
    end
  end
  object Timer_start: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer_startTimer
    Left = 32
    Top = 184
  end
end
