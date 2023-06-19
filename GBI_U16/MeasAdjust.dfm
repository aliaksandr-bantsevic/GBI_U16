object Form_MeasAdjust: TForm_MeasAdjust
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
  ClientHeight = 164
  ClientWidth = 645
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
  object Label1: TLabel
    Left = 8
    Top = 75
    Width = 99
    Height = 18
    Caption = #1052#1072#1088#1082#1080#1088#1086#1074#1082#1072':'
  end
  object Label2: TLabel
    Left = 26
    Top = 40
    Width = 82
    Height = 18
    Caption = 'C'#1082#1074#1072#1078#1080#1085#1072':'
  end
  object Label3: TLabel
    Left = 21
    Top = 8
    Width = 87
    Height = 18
    Caption = #1055#1083#1086#1097#1072#1076#1082#1072':'
  end
  object Button_apply: TButton
    Left = 516
    Top = 134
    Width = 121
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 0
    OnClick = Button_applyClick
  end
  object Button_cancel: TButton
    Left = 384
    Top = 134
    Width = 126
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 1
    OnClick = Button_cancelClick
  end
  object Edit_mark: TEdit
    Left = 128
    Top = 72
    Width = 509
    Height = 26
    TabOrder = 2
    Text = 'Edit_mark'
  end
  object StaticText_place: TStaticText
    Left = 128
    Top = 8
    Width = 131
    Height = 22
    Caption = 'StaticText_place'
    TabOrder = 3
  end
  object StaticText_drill: TStaticText
    Left = 128
    Top = 36
    Width = 122
    Height = 22
    Caption = 'StaticText_drill'
    TabOrder = 4
  end
end
