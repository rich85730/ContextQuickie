package contextquickie.tools;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author ContextQuickie
 *
 *         Wrapper class for starting processes.
 */
public final class ProcessWrapper
{
  /**
   * Prevents from creating instances.
   */
  private ProcessWrapper()
  {
  }

  /**
   * Executes a command with the passed arguments.
   * 
   * @param command
   *          The command to execute.
   * @param arguments
   *          The arguments of the command.
   */
  public static void executeCommand(final String command, final String... arguments)
  {
    executeCommand(command, Arrays.asList(arguments));
  }

  /**
   * Executes a command with the passed arguments.
   * 
   * @param command
   *          The command to execute.
   * @param arguments
   *          The arguments of the command.
   */
  public static void executeCommand(final String command, final List<String> arguments)
  {
    final List<String> commandAndArguments = new ArrayList<String>();
    commandAndArguments.add(command);
    for (String parameter : arguments)
    {
      if (parameter.contains(" "))
      {
        commandAndArguments.add(StringUtil.quoteString(parameter));
      }
      else
      {
        commandAndArguments.add(parameter);
      }
    }
    final ProcessBuilder processBuilder = new ProcessBuilder(commandAndArguments);
    try
    {
      processBuilder.start();
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }

  }
}
