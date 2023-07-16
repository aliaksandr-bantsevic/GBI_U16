object Form_DepthAdjust: TForm_DepthAdjust
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1086#1090#1084#1077#1090#1082#1080
  ClientHeight = 135
  ClientWidth = 242
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 18
  object Label1: TLabel
    Left = 16
    Top = 19
    Width = 64
    Height = 18
    Caption = #1059#1088#1086#1074#1077#1085#1100
  end
  object Label_tuberr: TLabel
    Left = 16
    Top = 51
    Width = 68
    Height = 18
    Caption = #1055#1086#1075#1088'. '#1090#1088'.'
  end
  object Button_enter: TButton
    Left = 25
    Top = 94
    Width = 97
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 0
    OnClick = Button_enterClick
  end
  object Button2: TButton
    Left = 128
    Top = 94
    Width = 97
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 1
    OnClick = Button2Click
  end
  object Edit_depth: TEdit
    Left = 128
    Top = 16
    Width = 97
    Height = 26
    TabOrder = 2
    OnKeyDown = Edit_depthKeyDown
  end
  object Edit_trerr: TEdit
    Left = 128
    Top = 48
    Width = 97
    Height = 26
    TabOrder = 3
  end
end
