package contextquickie.handlers.tortoise.svn;

import contextquickie.handlers.tortoise.TortoiseMergeCommand;
import contextquickie.preferences.PreferenceConstants;

public class TortoiseSvnMergeCommand extends TortoiseMergeCommand
{
  @Override
  protected String getMergeCommandPathName()
  {
    return PreferenceConstants.TortoiseSvn.getMergePath();
  }
}
